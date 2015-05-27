var redXImageSmall = "<img src='/pict/red_x.png' alt='X' width='10px' height='10px'/>";
var redXImage = "<img src='/pict/red_x.png' alt='X' width='20px' height='20px'/>";
var waitingForPlayer;
var gamePlaying;
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
		debugger;
		if(data.GameMode == "ONGOING"){
			document.getElementById("pop_up").style.display = "none";
			alert("Drugi gracz polaczony");
			stopWaitingForPlayer();
		}
	});	
};


ConnectPlayer = function(){
	
	$.ajax({
		url:"srvmyapp/ajax/statkipy/ConnectPlayer"		
	})
	
	.success(function(data){	
		var ownShipsPos = data.MyShips;
		ID=data.ID;
		arrangeShips(ownShipsPos, "ownTable", false);
	});
};

Update = function(_pID){	
	$.ajax({
		url:"srvmyapp/ajax/statkipy/Update",
		data: { playerID : _pID }
	})
	
	.success(function(data){
		debugger;
		whichPlayer(data.ID);
		if(data.ID == ID){
			arrangeShips(data.EnemyShots, "ownTable", true);			
			document.getElementById("enemyTable").cursor = "pointer";
		}
		else{
			$("enemyTable").unbind();
			$("enemyTable").removeAttr("onclick");
			document.getElementsByTagName("enemyTable td").cursor = "not-allowed !important";
			
		}
		if(data.GameMode != "ONGOING"){
			stopWaitingForMove();
		}
	});	
};

function arrangeShips(shipsPositions, tableId, ifAddImg) {
	var table = document.getElementById(tableId);
	if (shipsPositions){
	var ships = shipsPositions.split(";");
		for(i=0; i < ships.length-1; ++i){
			var ship = ships[i].split("-");
			if (!ifAddImg)
			{
				table.rows[parseInt(ship[0])+1].cells[parseInt(ship[1])+1].style.background = '#64b167';
			}
			else
			{
				table.rows[parseInt(ship[0])+1].cells[parseInt(ship[1])+1].innerHTML = redXImageSmall;
			}
		}
	}
}

window.onload = function () {
	setEnemyTable();
	$("body").append('<div id="pop_up" class="pop_up">');
	var pop = document.getElementById("pop_up");
	pop.innerHTML='<div id="message" class="message" ><br/><h4>Aby rozpoczac gre, kliknij ponizszy przycisk:</h4><br /><br/><button id="startButton" class="startButton" onclick=startGame()>START</button></div>';
	
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
				Shoot(ID, (this.rowIndex-1), this.positionIndex);
				tableText(this.rowIndex, this.positionIndex);
			};
		}
	}
	
}

function startGame() {
	disableButton();
	ConnectPlayer();
	waitingForPlayer = setInterval(function(){ myTimer() }, 1000);
}

function tableText(row, col) {
    var colName = document.getElementById("enemyTable").rows[0].cells[col+1].innerHTML;
	document.getElementById("selectedCell").innerHTML=colName +" "+ row;
	var cell = document.getElementById("enemyTable").rows[row].cells[col+1];
	cell.innerHTML = (!cell.innerHTML) ? redXImage : '';

}

function myTimer() {
	GetGameState(ID);
}

function myGameTimer() {
	Update(ID);
}

function stopWaitingForPlayer() {
    clearInterval(waitingForPlayer);
	gamePlaying = setInterval(function(){ myGameTimer() }, 1000);
}

function stopWaitingForMove() {
    clearInterval(gamePlaying);
}

function disableButton() {
	var img = document.createElement("img");
	img.src = "/pict/loader.gif";
	img.height = 50;
	img.width = 50;

	var txt = document .createElement("txt");
	txt.innerHTML = " Oczekiwanie na drugiego gracza";
	
	var src = document.getElementById("message");
	src.innerHTML = "<br /><br /><br />";
	src.appendChild(img);
	src.appendChild(txt);
}

function whichPlayer(playerId){
	var playerInfoText = document.getElementById("playerInfo");
	if (playerId == ID){
		playerInfoText.innerHTML = "Twoja kolej!";
	}
	else {
		playerInfoText.innerHTML = "Kolej przeciwnika";
	}
	
}


