var squares = document.getElementsByClassName("square");
var colors = signColors(6);
var pickedColors = pickColor();
var state = "hard";

var resetButton = document.getElementById("newGame");
resetButton.addEventListener("click", generateNewGame);
document.getElementById("newGame").innerHTML = "reset colors"
var display = document.getElementById("rgb");
var color;

/* buttons */
var easyBtn = document.getElementById("easyBtn");
easyBtn.addEventListener("click", function changeMarked(){
    console.log("easy pressed, state: " + state);
    if(state === "hard")
    {
        easyBtn.classList.add("selected");
        hardBtn.classList.remove("selected");

        colors = signColors(3);
        pickedColors = pickColor();
        displayRGB(3);

        for(var i = 3; i < squares.length; i++)
        {
            squares[i].style.display = "none"
        }
        
        state = "easy";
        document.getElementById("upper").style.backgroundColor = "rgb(203, 214, 175)";
    }
    
});
var hardBtn = document.getElementById("hardBtn");
hardBtn.addEventListener("click", function changeMarked(){
    console.log("hard pressed, state: " + state);
    if(state == "easy")
    {
        hardBtn.classList.add("selected");
        easyBtn.classList.remove("selected");
    
        colors = signColors(6);
        pickedColors = pickColor();
        displayRGB(6);
    
        for(var i = 3; i < squares.length; i++)
        {
            squares[i].style.display = "block"
        }
    
        state = "hard";
        document.getElementById("upper").style.backgroundColor = "rgb(203, 214, 175)";
    }
});

displayRGB(6);

function displayRGB(num)
{
    var randNum = Math.floor(Math.random()*(num - 1));
    color = squares[randNum].style.backgroundColor;
    display.textContent = color;
    console.log("picked: " + randNum);
}

function pickColor(){
    for(var i = 0; i < squares.length; i++)
    {
        squares[i].style.backgroundColor = colors[i];
        squares[i].addEventListener("click", changeColor);
    }
}


function signColors(num)
{
    var arr = [];
    for(var i = 0; i < num; i++)
    {
        arr[i] = randomColor();
    }

    return arr;
}
function randomColor(){
    var r = Math.random()*256;          // Random between 0-255
    var g = Math.random()*256;          // Random between 0-255
    var b = Math.random()*256;          // Random between 0-255

    return "rgb(" + r + ", " + g + ", " + b + ")";
}



function changeColor(){
    /* winning */
    if(this.style.backgroundColor === color)
    {
        document.getElementById("upper").style.backgroundColor = color;
        changeElsesColor();
        resetButton.textContent = "new game"
    }

    else{
        this.style.backgroundColor = "bisque";
    }
}

function changeElsesColor()
{
    for(var i = 0; i < squares.length; i++)
    {
        squares[i].style.backgroundColor = color;
    }
}

/* resets the colors if the 'new game' button was clicked */
function generateNewGame()
{
    if(state == "easy")
    {
        colors = signColors(3);
        pickedColors = pickColor();
        color = squares[Math.floor(Math.random()*(3))].style.backgroundColor;
    }
    else{
        colors = signColors(6);
        pickedColors = pickColor();
        color = squares[Math.floor(Math.random()*(6))].style.backgroundColor;
    }
    
    
    display.textContent = color;
    document.getElementById("upper").style.backgroundColor = "rgb(203, 214, 175)";
    resetButton.textContent = "reset colors"
/*
    if(state == "hard")
    {
        for(var i = 3; i < squares.length; i++)
        {
            squares[i].style.display = "block"
        }
    }
  */  
}


