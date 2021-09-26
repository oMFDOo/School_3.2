<!-- html 넣는 곳 -->
<template>
  <img alt="Vue logo" src="./assets/logo.png">
  <div>
    <h2 :style="textStyle">{{products[0]}} 학생</h2>
    <p>{{subject1}} 재학</p>
    <p>학번 : {{studentNum}}</p>
  </div>
  <div>
    <h2 :style="textStyle">{{products[1]}} 학생</h2>
    <p>{{subject1}} 재학</p>
    <p>학번 : {{studentNum}}</p>
  </div>
  <div>
    <h2 :style="textStyle">{{products[2]}} 학생</h2>
    <p>{{subject1}} 재학</p>
    <p>학번 : {{studentNum}}</p>
  </div>
</template>


<!-- js 넣는 곳 -->
<script>
export default {
  name: 'App',
  // 데이터 바인딩
  data(){
    // object 자료형으로 데이터 저장
    return {
      name1 : "황진주",
      subject1 : "응용소프트웨어공학과",
      studentNum : 20193148,
      textStyle : "color : blue",
      products : ['황진주', '아기 고양이', '씐난당']
    }
  },
  components: {
    
  }
}
</script>


<!-- css 넣는 곳 -->
<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
