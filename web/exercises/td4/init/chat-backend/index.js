"use strict;";

const express = require("express");
const faker = require("faker");
const cors = require("cors");
const bodyParser = require("body-parser");

const Sequelize = require("sequelize");

// Initialisation serveur
const app = express();

// Configuration Faker
faker.locale = "fr";

// Sécurité
app.use(cors());

// Configuration parser body
app.use(bodyParser.json());

// Route /
app.get("/", function(req, res) {
  res.send("Server is OK :)");
});

/* Partie Sequelizer */

// Connexion à la base de donnée avec Sequelize
const sequelize = new Sequelize("sqlite:database-chat.db");

// Modèle Message avec Sequelize
const Message = sequelize.define("message", {
  author: {
    type: Sequelize.STRING
  },
  content: {
    type: Sequelize.STRING
  }
});

// Modèle User avec Sequelize
const User = sequelize.define("user", {
  username: {
    type: Sequelize.STRING
  },
  password: {
    type: Sequelize.STRING
  }
});

// Création des tables
Message.sync({ force: true }).then(() => console.log("Table message créée"));
User.sync({ force: true }).then(() => {
  console.log("Table user créée");
  User.create({
    username: "alice",
    password: "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"
  });
  User.create({
    username: "bob",
    password: "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"
  });
});

// Création d'utilisateurs

// Récupération de tous les messages avec Sequelizer
app.get("/messages", function(req, res) {
  Message.findAll({ order: sequelize.literal("createdAt DESC") }).then(
    messages => {
      res.send(messages);
    }
  );
});

// Ajout d'un message avec Sequelizer
app.post("/messages", function(req, res) {
  const author = req.body.author;
  const content = req.body.content.replace(/\'/g, "''");
  Message.create({
    author: author,
    content: content
  }).then(() => res.status(201).send("Message created"));
});

// Génération de 10 messages aléatoires avec Sequelizer
app.post("/messages/generate", function(req, res) {
  for (let i = 0; i < 10; i++) {
    let author = faker.name.firstName();
    let content = faker.lorem.sentence();
    Message.create({
      author: author,
      content: content
    });
  }
  res.status("201").send("10 Messages created");
});

// Suppression d'un message avec Sequelizer
app.delete("/messages/:id", function(req, res) {
  const id = req.params.id;
  Message.destroy({
    where: {
      id: id
    }
  }).then(res.status("200").send("Message deleted"));
});

// Génération de 10 messages aléatoires avec Sequelizer
app.post("/login", function(req, res) {
  const username = req.body.username;
  const password = req.body.hashedPassword;
  User.findAll({
    where: {
      username: username,
      password: password
    }
  }).then(users => {
    if (users.length > 0) {
      res.status("200").send("Access granted");
    } else {
      res.status("403").send("Access denied");
    }
  });
});

/* Démarrage serveur */
app.listen(3000, function() {
  console.log("Serveur chat-backend démarré !");
});
