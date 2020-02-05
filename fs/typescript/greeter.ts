type RankingTuple = [number, string, boolean];

// 2 - defining typed variables
let position: number;

let playerName: string;
let finishedGame: boolean;
let ranking: RankingTuple;
let hallOfFame: Array<RankingTuple> = [];

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
function printRankings(rankings: Array<RankingTuple>): void {
  for (let ranking of rankings) {
    console.log(ranking);
  }
};

// 6 - calling the function
printRankings(hallOfFame);
