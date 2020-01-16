
function add(first, second, callback)
{
    setTimeout(() => {
        callback(first + second)}
        , 2000)
}
add(1, 4, (sum) => {
    console.log(sum)
})