/// @file test01_basic.js
/// @brief client unit tests, check the qunit testing library

module( "test01_basic", {
  setup: function() { },
  teardown: function() { }
});

test( "trivial test for qunit", function() {
    ok( 1 == "1", "Passed!" );
});

test( "please remember to copy body tag from src/index.html into tests/qu-test.html every time index.html is changed!", function() {
    ok( 1 == "1", "Passed!" );
});

test( "simple click test", function( assert ) {
  assert.expect( 1 );
 
  var $body = $( "body" );
 
  $body.on( "click", function() {
    assert.ok( true, "body was clicked!" );
  });
 
  $body.trigger( "click" );
});

test("ConnectPlayer returns player ID", function(){
		ConnectPlayer();
	notEqual (ID, "", "ID is not null");
});

test("Check if whichPlayer function set proper gui elements for active player", function(){
	ID='99';
	var yourTurn ="";
	var htmlFake =  $( "#qunit-fixture" );
	htmlFake.append("<span id='enemyTable'></span>" );
	htmlFake.append("<span id='playerInfo'></span>" );
	whichPlayer(99);
	ok ( tableClickable == true, "Proper table is clicable" );
	ok (document.getElementById("playerInfo") .style.color = "green", "Text has proper color");
	ok (document.getElementById('enemyTable').style.cursor == "pointer", "Table has proper pointer");

});

test("Check if whichPlayer function set proper gui elements for not active player", function(){
	ID='99';
	var opTurn ="";
	var htmlFake =  $( "#qunit-fixture" );
	htmlFake.append("<span id='enemyTable'></span>" );
	htmlFake.append("<span id='playerInfo'></span>" );
  
	whichPlayer(66);
	ok ( tableClickable == false, "Proper table is not clicable" );
	ok (document.getElementById('enemyTable').style.cursor == "not-allowed", "Table has proper pointer");
	ok (document.getElementById("playerInfo") .style.color = "red", "Text has proper color");
		
});

test( "Simple test to appends a div", function( assert ) {
  var fixture = $( "#qunit-fixture" );
 
  fixture.append( "<div>hello!</div>" );
  assert.equal( $( "div", fixture ).length, 1, "div added successfully!" );
});
 
test( "Simple test to appends a span", function( assert ) {
  var fixture = $( "#qunit-fixture" );
 
  fixture.append("<span>hello!</span>" );
  assert.equal( $( "span", fixture ).length, 1, "span added successfully!" );
});