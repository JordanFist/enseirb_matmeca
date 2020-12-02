'use strict;'

const express = require('express');
const faker = require('faker');
const cors = require('cors');
const bodyParser = require('body-parser');

const sqlite3 = require('sqlite3').verbose();
const Sequelize = require('sequelize');

// Initialisation serveur
const app = express();

// Configuration Faker
faker.locale = 'fr';

// Sécurité
app.use(cors());

// Configuration parser body
app.use(bodyParser.json());

// Route /
app.get('/', function (req, res) {
  res.send('Server is OK :)');
});

/* Partie SQLite */
/* // Connexion à la base de donnée avec sqlite
const db = new sqlite3.Database('database-chat.db');
// Initialisation de la table message
db.run('DROP TABLE IF EXISTS message;', () => {
  db.run('CREATE TABLE message(author TEXT, content TEXT, date TEXT);', () => {
    console.log('Table message créée');
  });
});

// Récupération de tous les messages avec Sqlite
app.get('/messages', function (req, res) {
  db.all('SELECT rowid, * FROM message ORDER BY date DESC', (err, rows) => {
    res.send(rows);
  });
});

// Ajout d'un message avec Sqlite
app.post('/messages', function (req, res) {
  const author = req.body.author;
  const content = req.body.content.replace(/\'/g, "''");
  const sqlQuery = "INSERT INTO message VALUES('" + author + "', '" + content + "', DATETIME('now', 'localtime'))";
  console.log(sqlQuery);
  db.run(sqlQuery);
  res.status(201).send('Message created');
});

// Génération de 10 messages aléatoires avec Sqlite
app.post('/messages/generate', function (req, res) {
  for (let i = 0; i < 10; i++) {
    let author = faker.name.firstName();
    let content = faker.lorem.sentence();
    db.run("INSERT INTO message VALUES('" + author + "', '" + content + "', DATETIME('now', 'localtime'))");
  }
  res.send('10 Messages created');
});

// Suppression d'un message avec Sqlite
app.delete('/messages/:id', function (req, res) {
  const id = req.params.id;
  db.run("DELETE FROM message WHERE rowid = " + id);
  res.status('200').send('Message deleted');
}); */

/* Partie Sequelizer */

// Connexion à la base de donnée avec Sequelize
const sequelize = new Sequelize('sqlite:database-chat.db');

// Modèle Message avec Sequelize
const Message = sequelize.define('message', {
  author: {
    type: Sequelize.STRING
  },
  content: {
    type: Sequelize.STRING
  }
});

// Création de la table
Message.sync({ force: true })
  .then(() => console.log('Table message créée'));

// Récupération de tous les messages avec Sequelizer
app.get('/messages', function (req, res) {
  Message.findAll({ order: sequelize.literal('createdAt DESC') }).then(messages => {
    res.send(messages);
  })
});

// Ajout d'un message avec Sequelizer
app.post('/messages', function (req, res) {
  const author = req.body.author;
  const content = req.body.content.replace(/\'/g, "''");
  Message.create({
    author: author,
    content: content
  }).then(() => res.status(201).send('Message created'));
});

// Génération de 10 messages aléatoires avec Sequelizer
app.post('/messages/generate', function (req, res) {
  for (let i = 0; i < 10; i++) {
    let author = faker.name.firstName();
    let content = faker.lorem.sentence();
    Message.create({
      author: author,
      content: content
    });
  }
  res.status('201').send('10 Messages created');
});

// Suppression d'un message avec Sequelizer
app.delete('/messages/:id', function (req, res) {
  const id = req.params.id;
  Message.destroy({
    where: {
      id: id
    }
  }).then(res.status('200').send('Message deleted'));
});

/* Démarrage serveur */
app.listen(3000, function () {
  console.log('Serveur chat-backend démarré !');
});
