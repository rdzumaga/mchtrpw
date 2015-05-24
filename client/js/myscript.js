var redXImage = "<img src='/pict/red_x.png' alt='X' width='10px' height='10px'/>";

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

function doOnLoad() {
		$.ajax({
		url:"srvmyapp/ajax/statkipy/ConnectPlayer"
		
	})

	.success(function(data){
		var enemyShots = data.EnemyShots;
		var ownTable = document.getElementById("ownTable");
		if (enemyShots){
			var shots = enemyShots.split(";");
			for(i=0; i < shots.length-1; ++i){
				var shot = shots[i].split("-");
				ownTable.rows[parseInt(shots[0])+1].cells[parseInt(shots[1])+1].innerHTML = redXImage;
		}
	}
	debugger;
			
	});
}

