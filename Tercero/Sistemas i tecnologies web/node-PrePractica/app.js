function Tokenizer(){
    this.dictionary = [];

    this.f = null

    this.contaDoor=(function(){
      var count=0
      return function(o=0){
        return (o!=0 ? count:count++)
      }
    })()

    this.run = function(llista){
      var auxDict=this.dictionary
      var funcAux= this.f
      //console.log(funcAux.toString())
      llista.forEach(function(element){
        if(auxDict[element]==undefined){
          //console.log('fuera: ' + element)
          if(funcAux!=null){funcAux()}
        }
        else{auxDict[element]()}//console.log('dentro: ' + element)}//auxDict[element]()}
       // console.log(auxDict[element])
      })
      this.dictionary = auxDict
      //console.log(this.dictionary)
    }

    this.on = function(c, f){this.dictionary[c] = f} 

    this.onDefault = function(pasamela){this.f=pasamela}
}


function testTokenizer(){
  
  var t = new Tokenizer();
  var countA = 0;
  var countC = 0;
  var countAll=0;
  var testString = ['H','o','l','a',' ','c','o','m',' ','a','n','e','u','?'];

  t.on('a', (function(){
      var count=0
      return function(o=0){
       return (o!=0 ? count:count++)
      }
    })());

  t.on('c', (function(){
      var count=0
      return function(o=0){
        return (o!=0 ? count:count++)
      }
    })());
  
  t.onDefault(t.contaDoor);
  //t.toString()
  t.run(testString)

  countA = t.dictionary['a'](2)
  countC = t.dictionary['c'](2)
  countAll = t.contaDoor(2)
  //here goes the code to run the test over testString
  
  console.log("numero de a's: " + countA);
  console.log("numero de c's: " + countC);
  console.log("numero d'altres caracters: " + countAll);
}

testTokenizer();

