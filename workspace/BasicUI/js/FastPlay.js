function Play(a){
	
	var word_list = [];
	var translate_list = [];
	var msg, trnslt;
	word_list = document.forms["Eng"].elements["EngW"].value.split("\n");
	translate_list = document.forms["Trnslt"].elements["Transl"].value.split("\n");
	
	
	for(var i = 0; i < word_list.length; i++)
	{
		msg = new SpeechSynthesisUtterance(word_list[i]);
		trnslt = new SpeechSynthesisUtterance(translate_list[i]);
		msg.lang = 'en-US';
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
		if(i == word_list.length-1)
		{
			i = 0;
		}
	}
}