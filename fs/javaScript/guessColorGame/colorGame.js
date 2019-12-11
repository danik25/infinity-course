var squares = document.getElementsByClassName("square");

for(var i = 0; i < squares.length; i++)
{
    squares[i].style.backgroundColor = randomColor();
}

function randomColor(){
    var r = Math.floor(Math.random()*256);          // Random between 0-255
    var g = Math.floor(Math.random()*256);          // Random between 0-255
    var b = Math.floor(Math.random()*256);          // Random between 0-255

    return "rgb(" + r + ", " + g + ", " + b + ")";
}
