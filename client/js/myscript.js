var redXImage = "<img src='/pict/red_x.png' alt='X' width='10px' height='10px'/>";
var ID;

Shoot = function(_pID, _i, _j){
	$.ajax({
		url:"srvmyapp/ajax/statkipy/Shoot",
		data: { playerID : _pID, pos_i : _i, pos_j : _j }
	})
	
	.success(function(data){
		//alert(data);
	});
}

GetGameState = function(_pID){
	
	$.ajax({
		url:"srvmyapp/ajax/statkipy/GetGameState",
		data: { playerID : _pID }
	})
	
	.success(function(data){
		//alert(data);
	});	
};


ConnectPlayer = function(){
	
	$.ajax({
		url:"srvmyapp/ajax/statkipy/ConnectPlayer"
		
	})
	
	.success(function(data){
	
	var ownShipsPos = data.MyShips;
	ID=data.ID;
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
	
	setEnemyTable();
	$("body").append('<div id="pop_up">');
	var pop = document.getElementById("pop_up");
	pop.innerHTML='<div class="pop_up" ><h1>hello</h1></div>';
	debugger;
// }
		// $.ajax({
		// url:"srvmyapp/ajax/statkipy/ConnectPlayer"
		
	// })

	// .success(function(data){
		// var enemyShots = data.EnemyShots;
		// var ownTable = document.getElementById("ownTable");
		// if (enemyShots){
			// var shots = enemyShots.split(";");
			// for(i=0; i < shots.length-1; ++i){
				// var shot = shots[i].split("-");
				// ownTable.rows[parseInt(shots[0])+1].cells[parseInt(shots[1])+1].innerHTML = redXImage;
		// }
	// }
	// debugger;
			
	// });
}

window.onload = function () {
	setEnemyTable();
	$("body").append('<div id="pop_up" class="pop_up">');
	var pop = document.getElementById("pop_up");
	pop.innerHTML='<div class="message" ><br/><h4>Aby rozpoczac gre, kliknij ponizszy przycisk:</h4><br /><br/><button id="guzik" class="startButton" onclick=startGame()>START</button></div>';
	
}

function setEnemyTable() {
	var table = document.getElementById('enemyTable');
	var rows = table.rows;

	for (var i = 0; i < rows.length; i++) {
		var cells = rows[i].getElementsByTagName("td");
		for (var j = 0; j < cells.length; j++) {
			var cell = cells[j];
			cell.rowIndex = i;
			cell.positionIndex = j;
			console.log(cell);
			cell.onclick = function () {
				Shoot(ID, this.rowIndex, this.positionIndex);
			};
		}
	}
	
}

function startGame() {
	ConnectPlayer();
	var millisecondsToWait = 500;
setTimeout(function() {
    // Whatever you want to do after the wait
}, millisecondsToWait);
	ConnectPlayer();
	document.getElementById("pop_up").style.display = "none";
}


