// import express from 'express';
// const app = express();
// const port = 3000;
// app.get('/', (req, res) => {
//   res.send('The sedulous hyena ate the antelope!');
// });
// app.listen(port, err => {
//   if (err) {
//     return console.error(err);
//   }
//   return console.log(`server is listening on ${port}`);
// });
const start = callback => {
    setTimeout(() => {
        callback('Hello');
        setTimeout(() => {
            callback('And Welcome');
            setTimeout(() => {
                callback('To Async Await Using TypeScript');
            }, 4000);
        }, 1000);
    }, 1000);
};
start(text => console.log(text));
console.log("here");
//# sourceMappingURL=app.js.map