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


        console.log("결과임당" + rows["collation"]);

    } catch (err) {
        throw err;
    } finally {
        console.log("finally");
        if (conn) return conn.end();
    }
}


async function asyncFunct() {
    let ccc;
    ccc = await pooll.getConnection();
    ccc.query("SELECT SCHOOL_NAME FROM SCHOOL", function (err, result, fields) {
        if (err) {
            console.log(err);
            throw err;
        }

    });
}

asyncFunct();
// Insert
//asyncFunction("INSERT INTO SCHOOL(SCHOOL_NAME) VALUE ('이마대');", 'hifiveDB');
// Select
asyncFunction("SELECT SCHOOL_NAME FROM SCHOOL;", 'hifiveDB');
