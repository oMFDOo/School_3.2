//const { values } = require("core-js/core/array");

module.exports={
    productList:{
        query:'SELECT t1.* , t2.path, t3.category1,t3.category2,t3.category3 \
        FROM t_product t1, t_image t2, t_category t3 WHERE t1.category_id=t3.id AND t2.product_id=t1.id AND t2.type=1'
    },
    /* 만약 제품리스트 페이지에서 제품 상세 페이지로 넘어갈떼 제품?을 선택한 경우 상세페이지 생성을 위한 쿼리문*/
    productDetail:{
        query:'SELECT t1.* , t2.path, t3.category1,t3.category2,t3.category3 \
        FROM t_product t1, t_image t2, t_category t3 \
        WHERE t1.id=? and t2.type=3 AND t1.category_id=t3.id AND t2.product_id=t1.id'  
    },
    productMainImages:{
        query:'SELECT * FROM t_image WHERE product_id=? AND TYPE=2'      // ? 의 의미= 클릭시 넘어온 제품의 id의 파라미터를 입력받음
    },
    productInsert:{    // 로그인한 사용자만 이용할 수 있는 서비스
        // 로그인 권한 체크 기능 구현 예정
        query:'insert into t_product(product_name,product_price, delivery_price,add_delivery_price,tags,outbound_days,seller_id,category_id)\
         values(?,?,?,?,?,?,?,?);'
    },
    productImageInsert:{
        query:'insert into t_image(product_id,type,type,path) values(?,?,?)'
    },
    sellerList:{
        query:'select * from t_seller'
    }
}