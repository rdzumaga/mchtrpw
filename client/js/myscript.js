

DoStuff = function(){
	
	$.ajax({
		url:"srvmyapp/ajax/calcpy/getParam",
		data: { x : "3", y:"5"}
	})
	
	.success(function(data){
		//alert(data);
	});
	
	
};


DoMoreStuff = function(){
	
	$.ajax({
		url:"srvmyapp/ajax/statkipy/ConnectPlayer"
		
	})
	
	.success(function(data){

	document.getElementById("guzik").style.display = "none";
	var ownShipsPos = data.MyShips;
	arrangeShips(ownShipsPos);
	});
};

function arrangeShips(ownShipsPositions) {
	var ownTable = document.getElementById("ownTable");
	if (ownShipsPositions){
	var ships = ownShipsPositions.split(";");
		for(i=0; i < ships.length-1; ++i){
			var ship = ships[i].split("-");
			ownTable.rows[parseInt(ship[0])+1].cells[parseInt(ship[1])+1].style.background = '#64b167';
		}
	}
}



