function loadInitialContent() {
    document.getElementById("back-btn").style.visibility = "hidden";
    document.getElementById('game-content').innerHTML = `
        <h1 id="game-heading">Tic Tac Toe</h1>
        <p id="game-para">Welcome to our game!</p>
        <button onclick="loadSecondContent()" id="play-btn">Play</button>
        <button onclick="undoPurchaseClick()" id="undo-purchase-click">Get 2 undo moves for 100 coins</button>
    `;
  
    Module.ccall("refreshData", null, [], []);
}

function loadSecondContent() {
  document.getElementById("back-btn").style.visibility = "visible";
    document.getElementById('game-content').innerHTML = `
        <p id="which-one-para">Which game do you want to play?</p>
        <button onclick="loadAILogin()" id="ai-btn">AI</button>
        <button onclick="loadLogin()" id="mul-btn">Multiplayer</button>
    `;
}

function loadLogin() {
    document.getElementById('game-content').innerHTML = `
<h2>Player 1 Login</h2>
<div id="Multiplayer" style="display: none;">2</div> <!-- 1-AI 2-Multiplayer -->
<div> <!-- Update the action attribute with your login handling URL -->
      <div>
          <label for="player1-username">Username:</label>
          <input type="text" id="player1-username" name="player1-username" required>
      </div>
      <div>
          <label for="player1-password">Password:</label>
          <input type="password" id="player1-password" name="player1-password" required>
      </div>
      <div>
          <button id="player1-login" class="1" type="submit" onclick="LoginPlayer1()">Login</button>
      </div>
  </div>

  <h2>Player 2 Login</h2>
  <div> <!-- Update the action attribute with your login handling URL -->
      <div>
          <label for="player2-username">Username:</label>
          <input type="text" id="player2-username" name="player2-username" required>
      </div>
      <div>
          <label for="player2-password">Password:</label>
          <input type="password" id="player2-password" name="player2-password" required>
      </div>
      <div>
          <button id="player2-login" type="submit" onclick="LoginPlayer2()">Login</button>
      </div>
  </div>
  <div class="center-button">
          <button type="submit" onclick="showMenu()">Submit</button>
      </div>
    `

    Module.ccall("multiplayerChosen", null, [], []); // You have to look at this Module.ccall(), inside the C++ function is defined, you havet ocopy the name of the function
}

function LoginPlayer1() { // There it is
    let username1 = document.getElementById("player1-username").value;
    let password1 = document.getElementById("player1-password").value;

    Module.ccall("LoginUser1", null, ["number", "string", "string"], [1, username1, password1]);
}

function LoginPlayer2() {
    let username = document.getElementById("player2-username").value
    let password = document.getElementById("player2-password").value
    let indicator = document.getElementById("Multiplayer").innerText

    let username1 = document.getElementById("player1-username").value

    if (username1 == username) {
        alert("Usernames cannot be same");
        return;
    }

    Module.ccall("LoginUser2", null, ["number", "string", "string"], [2, username, password])
}

function showMenu() {
    if (document.getElementById(`player1-login`).style.visibility == "hidden" && document.getElementById(`player2-login`).style.visibility == "hidden") {
        document.getElementById('game-content').innerHTML = `
        <h1 id="tic-tac-toe-timer">Time: <span id="current-ttt-time">0m 0s</span></h1>
      <button onclick="continueMulGame()" style="visibility: hidden;" id="cont-mul">Continue</button>
    <h2 id="current-turn-heading"></h2>

<div class="grid-container">
<div class="grid-item" id="0" onclick="makeMove(this)">_</div>
<div class="grid-item" id="1" onclick="makeMove(this)">_</div>
<div class="grid-item" id="2" onclick="makeMove(this)">_</div>  
<div class="grid-item" id="3" onclick="makeMove(this)">_</div>
<div class="grid-item" id="4" onclick="makeMove(this)">_</div>
<div class="grid-item" id="5" onclick="makeMove(this)">_</div>  
<div class="grid-item" id="6" onclick="makeMove(this)">_</div>
<div class="grid-item" id="7" onclick="makeMove(this)">_</div>
<div class="grid-item" id="8" onclick="makeMove(this)">_</div>  
</div>

<div class="win-counter">
<p><span id="plr-1-counter-wins">Player X</span> Wins: <span id="x-wins">0</span></p>
<p><span id="plr-1-counter-loses">Player X</span> Loses: <span id="x-loses">0</span></p>
<p><span id="plr-2-counter-wins">Player O</span> Wins: <span id="o-wins">0</span></p>
<p><span id="plr-2-counter-loses">Player O</span> Loses: <span id="o-loses">0</span></p>
<p><span id="plr-1-coins">Player X</span> Coins: <span id="x-coins">0</span></p>
<p><span id="plr-2-coins">Player O</span> Coins: <span id="o-coins">0</p>
</div>
<button id="undo-button" onclick="undoMoveJS()">Undo</button>
    `
        Module.ccall("setCurrentPlrAtBegin", null, [], []);
        // let time = 50;
        // let boolVal = Module.ccall("checkGameRunning", "number", [], []);
        // console.log(boolVal);
        // let intervalID = setInterval(() => {
        //     //countdown for 1 minute in descending order
        //     // first set a default time
        //     if (Module.ccall("checkGameRunning", "number", [], []) == false) {
        //         clearInterval(intervalID);
        //         return;
        //     }
        //     let timer = document.getElementById("current-ttt-time");
        //     timer.innerText = `${Math.floor(time/60)}m ${time % 60}s`;
        //     --time;
        //     if (time < 0) {
        //         clearInterval(intervalID);
        //         setTimeout(() => {
        //             alert("Time's up! Game draw!");
        //         }, 0);
        //         Module.ccall("endGame", null, [], []);
        //         document.getElementById('cont-mul').style.visibility = "visible";
        //         // Module.ccall("timesUp", null, [], []);
        //         // Module.timesUp();
        //     }
        // }, 1000);
        // Module.setCurrentPlrAtBegin();
    } else {
        alert("Please enter correct logins!");
    }
}

function undoMoveJS() {
    Module.ccall("undoMoveCPP", null, [], []);
}

function makeMove(cell) {
    Module.ccall("movePlr", null, ["string"], [cell.id]);
}

function makeMoveAIGame(cell) {
    Module.ccall("movePlr", null, ["string"], [cell.id]);
}

function continueMulGame() {
    Module.ccall("continueMulGame", null, [], []);
    document.getElementById('cont-mul').style.visibility = "hidden";
}

function continueAIGame() {
    Module.ccall("continueAIGame", null, [], []);
    document.getElementById('cont-ai').style.visibility = "hidden";
}

function LoginAIPlr() {
    let username = document.getElementById("player1-username").value
    let password = document.getElementById("player1-password").value
    let indicator = document.getElementById("AI").innerText

    Module.ccall("LoginUser1", null, ["number", "string", "string", "string"], [1, username, password])
}

function loadAILogin() {
    document.getElementById('game-content').innerHTML = `
    <h2>Player 1 Login</h2>
    <div id="AI" style="display: none;">1</div> <!-- 1-AI 2-Multiplayer -->
    <div> <!-- Update the action attribute with your login handling URL -->
          <div>
              <label for="player1-username">Username:</label>
              <input type="text" id="player1-username" name="player1-username" required>
          </div>
          <div>
              <label for="player1-password">Password:</label>
              <input type="password" id="player1-password" name="player1-password" required>
          </div>
          <div>
              <button id="player1-login" class="1" type="submit" onclick="LoginAIPlr()">Login</button>
          </div>
      </div>
      <div class="center-button">
              <button type="submit" onclick="showDifficultyMenu()">Submit</button>
          </div>
    `

    Module.ccall("AIGameChosen", null, [], []);
}

function showDifficultyMenu() {
  if (document.getElementById(`player1-login`).style.visibility == "hidden") {
    document.getElementById('game-content').innerHTML = `
    <h2>Choose Difficulty</h2>
    <button onclick="showAIMenu(0)" id="easy-btn">Easy</button>
    <button onclick="showAIMenu(4)" id="medium-btn">Medium</button>
    <button onclick="showAIMenu(9)" id="hard-btn">Hard</button>
    `
  } else {
    alert("Please enter correct logins!");
  }
}

function showAIMenu(difficulty) {
        document.getElementById('game-content').innerHTML = `
        <h1 id="tic-tac-toe-timer">Time: <span id="current-ttt-time">0m 0s</span></h1>
      <button onclick="continueAIGame()" style="visibility: hidden;" id="cont-ai">Continue</button>
      <div id="AI" style="display: none;">1</div> <!-- 1-AI 2-Multiplayer -->
    <h2 id="current-turn-heading"></h2>

<div class="grid-container">
<div class="grid-item" id="0" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="1" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="2" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="3" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="4" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="5" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="6" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="7" onclick="makeMoveAIGame(this)">_</div>
<div class="grid-item" id="8" onclick="makeMoveAIGame(this)">_</div>
</div>

<div class="win-counter">
<p><span id="plr-1-counter-wins">Player X</span> Wins: <span id="x-wins">0</span></p>
<p><span id="plr-1-counter-loses">Player X</span> Loses: <span id="x-loses">0</span></p>
<p>AI Wins: <span id="ai-wins">0</span></p>
<p>AI Loses: <span id="ai-loses">0</span></p>
<p><span id="plr-1-coins">Player X</span> Coins: <span id="x-coins">0</span></p>
</div>
    `
        Module.ccall("setCurrentPlrAtBeginAI", null, ["number"], [difficulty]);
        // let time = 50;
        // let boolVal = Module.ccall("checkGameRunning", "number", [], []);
        // console.log(boolVal);

        // let intervalID = setInterval(() => {
        //     //countdown for 1 minute in descending order
        //     // first set a default time
        //     if (Module.ccall("checkGameRunning", "number", [], []) == false) {
        //         clearInterval(intervalID);
        //         return;
        //     }
        //     let timer = document.getElementById("current-ttt-time");
        //     timer.innerText = `${Math.floor(time/60)}m ${time % 60}s`;
        //     --time;
        //     if (time < 0) {
        //         clearInterval(intervalID);
        //         setTimeout(() => {
        //             alert("Time's up! Game draw!");
        //         }, 0);
        //         Module.ccall("endGame", null, [], []);
        //         document.getElementById('cont-ai').style.visibility = "visible";
        //         // Module.ccall("timesUp", null, [], []);
        //         // Module.timesUp();
        //     }
        // }, 1000);
}

// For Undo, we are using "undo" as type of purchase
function undoPurchaseClick() {
    document.getElementById("back-btn").style.visibility = "visible";
    document.getElementById("game-content").innerHTML = `
    <div class="form__group field">
    <input type="input" class="form__field" id="username-field" placeholder="Name" required="">
    <label for="name" class="form__label">Username</label>
    </div>
       <button class="check-username-btn" onclick="sendUsername(document.getElementById('username-field').value, 'undo')">
        Buy
    </button>
    `
}

function sendUsername(value, typeOfPurchase) {
    Module.ccall("sendUsername", null, ["string", "string"], [value, typeOfPurchase])
}

function beforeReload() {
  Module.ccall("beforeReload", null, [], []);
}

window.addEventListener("beforeunload", beforeReload)