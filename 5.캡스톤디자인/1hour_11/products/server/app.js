// 웹서버 코드 구현 
//const { notDeepStrictEqual } = require('assert/strict');
const express = require('express');         // 설치한 express모듈 불러오기
const app=express();
const session= require('express-session');
const fs=require('fs');                // fs = file system으로 파일 디렉토리에 접근가능한 모듈

app.use (session({                    //    app에서 아래와 같이 설정한 session을 사용하겠다
    secret:'secret code',             //   ssesion에 대한 key설정 (키로 설정하고 싶은 문자열 입력)            
    resave:false,                     //  request 요청이 오면 세션에 수정사항이 없더라도 저장하시겠습니까?
    saveUninitialized:false,      
    cookie:{
        secure:false,                 //false로 설정해야 로그인의 여부에 따라 데이터 접근 제한 기능 수행가능
        maxAge:1000*60*60             //쿠키 유효시간 설정(1시간)
    }
}));

// 서버 출력 ( 생성?)
const server =app.listen(3000,()=>{
    console.log('Server Started. port 3000')    //웹서버 정상구동 시 출력

});  

// sql 문 수정 시 재시작 없이 수정사항 파악 후 바로 실행
let sql=require('./sql.js');

// fs의 모듈에서 watchFile()을 통해 수정사항 파악 
fs.watchFile(__dirname+'/sql.js',(curr,prev)=>{
    console.log('sql 변경시 재시작 없이 반영되도록 함.');
    delete require.cache[require.resolve('./sql.js')];  //서버 시작 했을때 반영되었던 sql문 삭제 
    sql=require('./sql.js');         // 다시 sql문을 다시 require()을 통해서 반영
});


// DB 접속 정보
const db={
    database:"dev", 
    connnectionLimit:10,
    host:"192.168.0.11",
    user:"root",
    password:"1234"
};

//'mysql'모듈에서 제공하는  createPool()함수를 이용하여 db 연동
// dbPool을 이용하여 퀴리문 작성
const dbPool=require('mysql').createPool(db);



// axios를 통해 get.post로 서버와 클라이언트 측 통신

// 클라이언트 측에서 post로 데이터 요청 시 app.post 사용
app.post('/api/login',async(request,res)=>{
    request.session['email']='paplove852@naver.com';
    res.send('ok');

});
app.post('/api/logout',async(request,res)=>{
    request.session.destroy();
    res.send('ok');
});




// 위의 '/api/login' 와 '/api/logout' 외 다른 api경로 접근 시 '/api/:alias'에서 모두 처리
// const req로 서버에서 받아온 데이터를 post방식으로 클라이언트 측에 응답

// 로그인 시에만 작동하는 서비스 
app.post('/apirole/:alias',async(request,res)=>{
    if(!request.session.email){
        return res.status(401).send({
            error:'You need to login.'
        });
    }
    try{
        res.send(await req.db(request.params.alias));
    } catch(err){ 
        res.status(500).send({
            error:err
        });
    }
});

// 로그인 정보 없이 조회가능 한 서비스
app.post('/api/:alias',async(request,res)=>{
   
    try{
        res.send(await req.db(request.params.alias));
    } catch(err){
        res.status(500).send({
            error:err
        });
    }
});


// mariaDB로 접근하여 데이터를 가져온다
// 데이터를 DB에 접근하여 insert하는 방식도 동일하다!
const req = {
    async db(alias, param = [], where = '') {  // t_product 의 id 가 where 파라미터의 매개변수로 입력
      return new Promise((resolve, reject) => dbPool.query(sql[alias].query + where, param, (error, rows) => {  //sql[alias].query => alias에 sql.js의 productList의 query 가 전달됨
        if (error) { 
          if (error.code != 'ER_DUP_ENTRY')
            console.log(error);
          resolve({
            error
          });
        } else resolve(rows);
      }));
    }
  };


  









