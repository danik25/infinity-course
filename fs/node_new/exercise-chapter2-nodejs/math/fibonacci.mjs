function fibonacciSync(n)
{
    if(n <= 1){
        return 1
    }

    return (fibonacciSync(n - 1) + fibonacciSync(n - 2))
}
function callback(param, func)
{
    console.log("i: " + param + " -> " + func(param))
}

(function iifeFib()
{
    var i;
    for(i = 0; i < 5; ++i)
    {
        setImmediate(callback, i, fibonacciSync)
    }
})()

