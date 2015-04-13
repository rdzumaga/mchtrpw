var redXImage = "<img src='/pict/red_x.png' alt='X' width='20px' height='20px'/>";

window.onload = function () {
	setEnemyTable();
	arrangeShips();
	
} 

function tableText(row, col) {
    var colName = document.getElementById("enemyTable").rows[0].cells[col+1].innerHTML;
	document.getElementById("selectedCell").innerHTML=colName +" "+ row;
	var cell = document.getElementById("enemyTable").rows[row].cells[col+1];
	cell.innerHTML = (!cell.innerHTML) ? redXImage : '';

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
        cell.totalCells = cells.length;
        cell.totalRows = rows.length;
        console.log(cell);
        cell.onclick = function () {
			tableText(this.rowIndex, this.positionIndex);
			//TODO podpiac logike
        };
    }
}
	
}

function arrangeShips() {
	//TODO podpiac logike, chwilowe rozwiazanie:
	var ownTable = document.getElementById("ownTable");
	ownTable.rows[1].cells[1].style.background = '#64b167';
	ownTable.rows[2].cells[1].style.background = '#64b167';
	ownTable.rows[4].cells[5].style.background = '#64b167';
	ownTable.rows[5].cells[5].style.background = '#64b167';
	ownTable.rows[6].cells[5].style.background = '#64b167';
	ownTable.rows[9].cells[4].style.background = '#64b167';
	ownTable.rows[9].cells[5].style.background = '#64b167';
	ownTable.rows[9].cells[6].style.background = '#64b167';
	ownTable.rows[9].cells[7].style.background = '#64b167';
}
