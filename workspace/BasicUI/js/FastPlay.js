
function Play()
{
	 
	 var yandex_translator = {
             lines : {},
             key:"dict.1.1.20171205T214425Z.b84e3547a503df3d.8a10897de7d9d51cf909f4279f337462cd980790",
             api : "https://dictionary.yandex.net/api/v1/dicservice.json/lookup",
             returned_text : ' ',
             translate : function (id,callback){
                 var text = id;
                 var url = this.api+'?';
                 var that = this;

                 url  +='key='+this.key;
                 url+= '&lang=en-ru';
                 url+= '&text='+text;


                 var ajax = new XMLHttpRequest();
                 ajax.open('GET',url,true);
                 ajax.onreadystatechange = function(){
                     if (ajax.readyState == 4){
                         if(ajax.status == 200){
                             that.lines[id] = text;
                             text = ajax.responseText;
                             text = JSON.parse(text);
                             text = text.def[0].tr[0].text;
                             var msg = new SpeechSynthesisUtterance(text);
                             console.log('Supported keys list');
                             window.speechSynthesis.speak(msg);
                         }
                     }
                 };
                 ajax.send(null);
             },
             revert : function(id){
                 document.getElementById(id).innerHTML = this.lines[id];

             }
         };
	 
	 
	 var word_list = [];
	 
	 word_list = document.forms["Eng"].elements["EngW"].value.split("\n");
	 var text = word_list[0];
     text = yandex_translator.translate(text);
     
        

         
	/*var word_list = [];
	var translate_list = [];
	var msg, trnslt;
	word_list = document.forms["Eng"].elements["EngW"].value.split("\n");
	translate_list = document.forms["Trnslt"].elements["Transl"].value.split("\n");
	//while(true)
	//{
		for(var i = 0; i < word_list.length; i++)
		{
			
			msg = new SpeechSynthesisUtterance(word_list[i]);
			trnslt = new SpeechSynthesisUtterance(translate_list[i]);
			msg.lang = 'en-US';
			if(a == 2)
			{
				window.speechSynthesis.cansel();
				return;
			}
			window.speechSynthesis.speak(msg);
			window.speechSynthesis.speak(trnslt);
			if(a == 0)
			{
				window.speechSynthesis.pause();
			}
			if(a == 1)
			{
				window.speechSynthesis.resume();
			
			}
			
		}
	//}*/
}