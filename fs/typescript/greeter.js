// 2 - defining typed variables
var position;
var myVar;
var playerName;
var finishedGame;
var ranking;
var hallOfFame = [];
// 3 - creating a ranking
position = 1;
playerName = "Bruno Krebs";
finishedGame = true;
ranking = [position, playerName, finishedGame];
hallOfFame.push(ranking);
// 4 - creating another ranking
position = 2;
playerName = "Maria Helena";
finishedGame = true;
ranking = [position, playerName, finishedGame];
hallOfFame.push(ranking);
// 5 - defining a function that logs all rankings
function printRankings(rankings) {
    for (var _i = 0, rankings_1 = rankings; _i < rankings_1.length; _i++) {
        var ranking_1 = rankings_1[_i];
        console.log(ranking_1);
    }
}
;
// 6 - calling the function
myVar = printRankings(hallOfFame);
console.log(myVar.bar);
