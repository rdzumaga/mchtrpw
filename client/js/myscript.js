var hitImgSmall = "<img src='/pict/red_x.png' alt='X' width='15px' height='15px'/>";
var hitImg = "<img src='/pict/red_x.png' alt='X' width='20px' height='20px'/>";
var missImg = "<img src='/pict/dot.png' alt='O' width='25px' height='25px'/>";
var missImgSmall ="<img src='/pict/dot.png' alt='O' width='15px' height='15px'/>";
var yourTurn = "<img src='/pict/play.png' alt='+' width='100px' height='100px'/>";
var opTurn ="<img src='/pict/STOP.png' alt='-' width='100px' height='100px'/>";
var winPict = "<img src='/pict/win.png' alt='-' width='100px' height='80px'/>";
var failPict = "<img src='/pict/fail.png' alt='-' width='100px' height='80px'/>";

var waitingForPlayer;
var gamePlaying;
var ID;
var tableClickable = true;

Shoot = function(_pID, _i, _j){
	$.ajax({
		url:"srvmyapp/ajax/statkipy/Shoot",
		data: { playerID : _pID, pos_i : _i-1, pos_j : _j }
	})
	
	.success(function(data){
				if(data.GameMode == "ONGOING"){
		tableText(_i, _j, data.TargetHit);
				}
	});
}

GetGameState = function(_pID){
	
	$.ajax({
		url:"srvmyapp/ajax/statkipy/GetGameState",
		data: { playerID : _pID }
	})
	
	.success(function(data){
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
		whichPlayer(data.ID);
		arrangeShips(data.EnemyShots, "ownTable", true);		
		
		if(data.GameMode != "ONGOING"){
			
			if(data.GameMode == "FINISHED"){
				if (data.ID == ID){
					addEndMessage(true);
				}
				else{
					addEndMessage(false);
				}
			}
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
			var cell = table.rows[parseInt(ship[0])+1].cells[parseInt(ship[1])+1];
	
			if (!ifAddImg)
			{
				cell.className = "occupied";
			}
			else
			{
				cell.innerHTML = (cell.className == "occupied") ? hitImgSmall : missImgSmall;
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
				if (tableClickable && cell.innerHTML == ""){
					Shoot(ID, (this.rowIndex), this.positionIndex);					
				}
			};
		}
	}
	
}

function startGame() {
	disableButton();
	ConnectPlayer();
	waitingForPlayer = setInterval(function(){ myTimer() }, 500);
}

function tableText(row, col, targetHit) {
    var colName = document.getElementById("enemyTable").rows[0].cells[col+1].innerHTML;
	var hit = (targetHit == 0) ? "pudło!" : "trafiony!"; 
	document.getElementById("selectedCell").innerHTML=colName +" "+ row + " - " + hit; 
	var cell = document.getElementById("enemyTable").rows[row].cells[col+1];
	cell.innerHTML = (targetHit == 0) ? missImg : hitImg;

}

function myTimer() {
	GetGameState(ID);
}

function myGameTimer() {
	Update(ID);
}

function stopWaitingForPlayer() {
    clearInterval(waitingForPlayer);
	gamePlaying = setInterval(function(){ myGameTimer() }, 500);
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
		playerInfoText.innerHTML = "TWOJA KOLEJ! <br/> " + yourTurn + "<br /><br /> ";
		playerInfoText.style.color = "green";
		document.getElementById('enemyTable').style.cursor = "pointer";
		document.getElementById('enemyTable').style.boxShadow = "0px 5px 10px #14A026";
		tableClickable = true;		
	}
	else {
		playerInfoText.innerHTML = "KOLEJ PRZECIWNIKA <br/> " + opTurn + "<br/><br /> ";
		tableClickable = false;
		document.getElementById('enemyTable').style.cursor = "not-allowed";
		document.getElementById('enemyTable').style.boxShadow  = "0px 5px 10px #F51414";
		playerInfoText.style.color = "red";
	}
	
}

function addEndMessage(winner){
	$("body").append('<div id="endMessage" class="pop_up">');
	var endMessage = document.getElementById("endMessage");
	var message = winner ? "<br />Wygrałeś !!! <br /><br /> "+winPict : "<br />Przegrałeś !!! <br /><br /> "+ failPict ;
	endMessage.innerHTML='<div id="endMsg" class="message" ><br/><h4>Gra zakonczona  ' + message + ' </h4><br /><br/></div>';
}
