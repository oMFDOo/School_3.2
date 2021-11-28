// var mariaDB = require('mysql');
// var db = mariaDB.createConnection({
// 	DBHost: '127.0.0.1',
// 	DBPort: 5555,
// 	DBUser: 'root',
// 	DBpass: '1234',
// 	connectionLimit : 8,
//     database:'opentutorials'
// });

// var connection = mariaDB.createConnection(conn); // DB 커넥션 생성
// connection.connect();   // DB 접속

// var testQuery = "INSERT INTO `members` (`username`,`password`) VALUES ('test','test');";

// connection.query(testQuery, function (err, results, fields) { // testQuery 실행
//     if (err) {
//         console.log(err);
//     }
//     console.log(results);
// });

// testQuery = "SELECT * FROM MEMBERS";

// connection.query(testQuery, function (err, results, fields) { // testQuery 실행
//     if (err) {
//         console.log(err);
//     }
//     console.log(results);
// });


// connection.end(); // DB 접속 종료


const mariadb = require('mariadb');

const pooll = mariadb.createPool({
    host: '127.0.0.1',
    port: '5555',
    user: 'root',
    password: '1234',
    database: 'hifiveDB',
    connectionLimit: 5
});

async function asyncFunction(query_, db_) {

    const pool = mariadb.createPool({
        host: '127.0.0.1',
        port: '5555',
        user: 'root',
        password: '1234',
        database: db_,
        connectionLimit: 5
    });

    console.log("start");
    let conn;
    try {
        conn = await pool.getConnection();
        console.log("try");
        const rows = await conn.query(query_);
        console.log(rows); //[ {val: 1}, meta: ... ]

    } catch (err) {
        throw err;
    } finally {
        console.log("finally");
        if (conn) return conn.end();
    }
}


async function asyncFunct(){
    let ccc;
    ccc = await pooll.getConnection();
    ccc.query("INSERT INTO SCHOOL(SCHOOL_NAME) VALUES('동동의대')", function(err, result, fields){
        if(err){
            console.log(err);
        } else {
            console.log(result);
        }
    });
}

asyncFunct();
asyncFunction("SELECT QUERY FROM LOG", 'hifiveDB');