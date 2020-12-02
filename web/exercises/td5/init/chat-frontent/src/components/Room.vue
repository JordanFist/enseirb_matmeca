<template>
  <b-container class="mx-auto mt-3">
    <b-row class="mx-auto mb-3">
       <b-alert show variant="secondary" class="float-left">Vous �tes connect�(e) en tant que <strong>{{username}}</strong></b-alert>
    </b-row>
    <b-row>
      <b-col cols="4">
        <b-form v-on:submit.prevent="addMessage" v-on:reset.prevent="onReset">
          <b-form-group
            id="formInputGroup"
            label="Votre message :"
            label-for="content"
            description="Restez poli svp."
          >
            <b-form-textarea
              id="content"
              v-model="form.content"
              placeholder="Je ..."
              :rows="3"
              :max-rows="6"
            ></b-form-textarea>
          </b-form-group>
          <b-button type="submit" variant="primary">Envoyer</b-button>
          <b-button type="reset" variant="danger">Reset</b-button>
        </b-form>
      </b-col>
      <b-col cols="8">Liste des messages :
        <b-list-group class="mt-2">
        <transition-group name="list">
          <message
            v-for="message in messages"
            v-bind:key="message.id"
            v-bind:username="username"
            v-bind:message="message"
            v-on:deleteMessage="deleteMessage"
            v-bind:class="{ right: message.author !== username }"
            class="message-item"
          ></message>
          </transition-group>
        </b-list-group>

      </b-col>
    </b-row>
  </b-container>
</template>


<script>
import axios from "axios";
import store from "../store";
import Message from "./Message.vue";
import io from "socket.io-client";

export default {
  mounted: function() {
    this.socket.on("MESSAGE_ADDED", message => {
    this.messages.unshift(message);
    });
    this.socket.on("MESSAGE_DELETED", message => {
    (id) => this.messages = this.messages.filter(message => message.id != id);
    });
  },
  components: {
    Message
  },
  data: function() {
    return {
      form: {
        content: ""
      },
      socket: io("http://chat-enseirb.us.openode.io/"),
      messages: []
    };
  },
  computed: {
    username: function() {
      return store.state.username;
    },
    loggedIn() {
      return store.state.loggedin;
    }
  },
  methods: {
    addMessage: function(event) {
      axios
        .post("http://chat-enseirb.us.openode.io/messages", {
          author: this.username,
          content: this.form.content
        })
        .then(response => {
          //this.loadMessages();
          this.form.content = "";
        })
        .catch(e => {
          console.error(e);
        });
    },
    onReset: function(evt) {
      this.form.content = "";
    },
    loadMessages: function() {
      axios
        .get("http://chat-enseirb.us.openode.io/messages")
        .then(response => {
          this.messages = response.data;
        })
        .catch(e => {
          console.error(e);
        });
    },
    deleteMessage: function(id) {
      axios
        .delete(`http://chat-enseirb.us.openode.io/messages/${id}`)
        .then(response => {
          //this.loadMessages();
        })
        .catch(e => {
          console.error(e);
        });
    }
  },
  created: function() {
    this.loadMessages();
  },
};
</script>


<style>
.material-icons:hover {
  cursor: pointer;
}
.v-align {
  vertical-align: middle;
}
.right {
  text-align: right;
}
.list-enter-active, .list-leave-active {
  transition: all 0.5s;
}

.list-enter.right, .list-leave-to.right {
  opacity: 0;
  transform: translateX(30px);
}

.list-enter, .list-leave-to {
  opacity: 0;
  transform: translateX(-30px);
}
</style>
