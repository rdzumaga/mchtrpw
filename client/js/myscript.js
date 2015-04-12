

DoStuff = function(){
	
	$.ajax({
		url:"srvmyapp/ajax/calcpy/getParam",
		data: { x : "3", y:"5"}
	})
	
	.success(function(data){
		alert(data);
	});
	
	
};


