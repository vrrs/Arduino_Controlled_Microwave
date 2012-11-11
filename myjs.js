var ip="192.168.1.3";
var size=0;
var codes="";

function setIP(opt){
 if (opt==0){
   if (event.keyCode==13){
	  ip=document.getElementById("ip").value;
	  document.getElementById("ipH").innerHTML="The Arduino Server IP:"+ip;
   }
 }
 else{
   ip=document.getElementById("ip").value;
   document.getElementById("ipH").innerHTML="The Arduino Server IP:"+ip;
}
}
   
function sub(opt){
  val="";
  if(opt==0){
	val=document.getElementById("txt").value;
  }
  else{
	val=size.toString()+codes;
  }
  errTextbox=document.getElementById("di");
  try{
	request=new XMLHttpRequest();
	request.open('get','http://'+ip+'?'+val,true);
	request.send();
  }
  catch(error){
   errTextbox.value=error;
 }
}

function subK(opt){
 if (event.keyCode==13){
	sub(opt);
 }
}

function addIns(code){
	if (size+1>9){
		alert("You can only send 9 instructions to Arduino.");
	}
	else{
		codes=codes+code;
		size=size+1;
		document.getElementById("txt").value=size.toString()+codes;
	}
}

function cl(){
	size=0;
	codes="";
	document.getElementById("txt").value=""
}