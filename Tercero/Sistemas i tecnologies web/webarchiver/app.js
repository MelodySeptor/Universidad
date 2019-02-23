var http = require('http');
var request = require('request');
var cheerio = require ('cheerio');
var stream = require('stream');
var fs = require('fs');
var path = require('path');
var url = require('url');
var validUrl = require('valid-url');
var archiver = require('archiver');
const { parse } = require('querystring');

/**
* Return a website error.
* res: Result
*/
function default_error(res){
  console.log("Error website launched")
  res.writeHead(200, {'Content-Type': 'text/html'})
  fs.createReadStream('./view/error.html').pipe(res)
}

/*
* Has a dictionary with all relation with URL-Translate.
* maxFiles: int
*/
function ReplaceManager(maxFiles){
  this._fileCounter = 0
  this._replaceMap = []
  //const _NOT_FOUND_FILE = "404.html"
  this._NOT_FOUND_FILE="404.html"
  this.lookupName = function(url){
    if(this._fileCounter==0){this._replaceMap[url] = "index.html"; this._fileCounter++; return this._replaceMap[url]}
    else if(this._fileCounter>=maxFiles && this._replaceMap[url]==undefined){return this._NOT_FOUND_FILE}
      else if(this._replaceMap[url]!=undefined){return this._replaceMap[url]}
        else {this._replaceMap[url] = this._fileCounter + ".html"; this._fileCounter++; return this._replaceMap[url]}
  }
}
ReplaceManager._NOT_FOUND_FILE="404.html"

/*
* Class to get all methods for URLs.
*/
function URLManager(){
}

URLManager.getResourceExtension = function(urlF){
  var extension = path.parse(url.parse(urlF).pathname).ext
  if(extension==''){
    extension = '.html'
  }
  return extension
}

URLManager.getDownloadableURL = function(urlParent, href){
  var urlAux=''
  var result=''
  if(href==undefined){urlAux=''}else{urlAux=href}
  if(!urlAux.startsWith("http")){
    result = url.resolve(urlParent, urlAux)
    if(!result.startsWith('http')){result = urlParent + urlAux}
  }
  else{result = urlAux}
  return result
}

//YA VIENE HECHO
function getTransformStream(url, recLevel, replaceManager, downloadedFiles, doCrawlAndDownloadResource) {
  var transformStream = new stream.Transform();
  var buffer='';

  transformStream._transform = function(chunk, encoding, callback) {    
    buffer += chunk.toString();
    callback();
  };

  transformStream._flush = function(callback){
    this.push(transformStream._replace(buffer));
    callback();
  }

  transformStream._replace = function(chunk){
      $ = cheerio.load(chunk);
      $('a').each(function (i, link){
        var newUrl = $(this).attr('href'); 
        var downloadableURL = URLManager.getDownloadableURL(url,newUrl);
        var newUrlName = replaceManager.lookupName(downloadableURL);
        $(this).attr('href', newUrlName);

        doCrawlAndDownloadResource(downloadableURL,
          recLevel - 1, replaceManager, newUrlName, downloadedFiles); 
      }); //end $a.each
      return $.html();
  }; 

  return transformStream;  
}

/**
* 
* req: Request
* res: Response
* queryReq: dictionary
*/
function startCrawling(req, res, queryReq){
  console.log("crawler start")
  var downloadedFiles=[]
  var replaceManager=new ReplaceManager(queryReq.maxFiles)
  var outputName=replaceManager.lookupName(queryReq.url)
  var zip = archiver('zip')
  var listCurrentDownload=[]

  if(validUrl.isUri(queryReq.url)){
    console.log('Download: ' + outputName + ' ' + queryReq.url)
    res.writeHead(200, {
      'Content-Type': 'application/zip',
      'Content-disposition': 'attachment; filename=files.zip'
    });
    zip.pipe(res)
    doCrawlAndDownloadResource(queryReq.url, queryReq.recLevel, replaceManager, outputName, downloadedFiles)
  }
  else{console.log("Invalid url" + queryReq.url); default_error(res)}
  /**
  * Download Body of URL.
  * url: string
  * recLevel: int
  * replaceManager: ReplaceManager
  * outputName: string
  * downloadedFiles: list[]
  */
  function doCrawlAndDownloadResource(url, recLevel, replaceManager, outputName, downloadedFiles){
    if(recLevel>0 && downloadedFiles.indexOf(url)==-1 && outputName!="404.html"){
      downloadedFiles.push(url)
      listCurrentDownload.push(url)
      var web = request.get(url)
      var transform = web.pipe(getTransformStream(url, recLevel, replaceManager, downloadedFiles, doCrawlAndDownloadResource))
      zip.append(transform, {name:outputName})
      transform.on('finish', function(){ 
        listCurrentDownload.splice(listCurrentDownload.indexOf(url),1)
        if(listCurrentDownload.length==0){zip.finalize()}
      })
   }
   else{
   } 
  }
}

/**
* Function server.
* req: Request
* Res: Response
*/
function routeRequests(req, res){
  console.log("req.url: " + req.url);

  //Default Form
  if(req.url == '/'){
    res.writeHead(200, {'Content-Type': 'text/html'})
    fs.createReadStream('./view/index.html').pipe(res)
  }
  else if(req.url=='/crawler'){
    console.log("crawler request init")
    let body = ''
    var queryReq
    req.on('data', chunk => {
        body += chunk.toString()
    })
    req.on('end', () => {
        queryReq=parse(body)
        console.log("Query request:")
        console.log(queryReq)
        //res.end('Getting files . . .')
        startCrawling(req, res, queryReq)
    })
  }
  else{
    console.log("No valid option")
    default_error(res)
  }
}

//Server parguela
http.createServer(routeRequests).listen(8081);
