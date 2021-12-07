<template>
  <form v-on:submit="submitForm"> <!-- 메서드 생성 -->
    <div>
      <label for="username">id: </label>
      <input id="username" type="text" v-model="username">
    </div>
    <div>
      <label for="password">password: </label>
      <input id="password" type="password" v-model="password">
    </div>
    <button type="submit">login</button>
  </form>
</template>
<script>
import axios from 'axios';

export default {
  data: function() {
    return {
      username: '',
      password: ''
    }
  },
  methods: { // 메서드 구현
    submitForm: function() {
      console.log(this.username, this.password);
      var url = 'https://jsonplaceholder.typicode.com/users';
      //이 url로 데이터를 보내고 받을 수 있음
      var data = {
        username: this.username,
        password: this.password
      }
      axios.post(url, data)
        .then(function(response){
          console.log(response);
        })
        .catch(function(error){
          console.log(error);
        })
    }
  }
}
</script>