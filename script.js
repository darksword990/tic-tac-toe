function loadInitialContent() {
    document.getElementById('game-content').innerHTML = `
        <h1 id="game-heading">Tic Tac Toe</h1>
        <p id="game-para">Welcome to our game!</p>
        <button onclick="loadSecondContent()" id="play-btn">Play</button>
        <button onclick="" id="achievement">Achievement</button>
    `;

    Module.ccall("refreshData", null, [], []);
}

function loadSecondContent() {
    document.getElementById('game-content').innerHTML = `
        <p>Which one?</p>
        <button onclick="loadThirdContent()">AI</button>
        <button onclick="loadLogin()">Multiplayer</button>
    `;
    Module.ccall("createGame", null, [], []);
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

    Module.ccall("createMultiplayer", null, [], []);
}

function LoginPlayer1() {
    let username1 = document.getElementById("player1-username").value
    let password1 = document.getElementById("player1-password").value
    let indicator = document.getElementById("Multiplayer").innerText

    Module.ccall("LoginUser1", null, ["number", "string", "string", "string"], [1, indicator, username1, password1])
    // Module.LoginUser1(1, indicator, username1, password1);
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

    Module.ccall("LoginUser2", null, ["number", "string", "string", "string"], [2, indicator, username, password])
    // Module.LoginUser2(2, indicator, username, password);
}

function loadThirdContent() {
    document.getElementById('game-content').innerHTML = `
        <button onclick="loadInitialContent()">Back</button>
    `;
}

function showMenu() {
    if (document.getElementById(`player1-login`).style.visibility == "hidden" && document.getElementById(`player2-login`).style.visibility == "hidden") {
        document.getElementById('game-content').innerHTML = `
      <button onclick="loadInitialContent()">Back</button>
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
<p>Player X Wins: <span id="x-wins">0</span></p>
<p>Player O Wins: <span id="o-wins">0</span></p>
</div>
<button onclick="undoMoveJS()">Undo</button>
    `
        Module.ccall("setCurrentPlrAtBegin", null, [], []);
        // Module.setCurrentPlrAtBegin();
    } else {
        alert("Please enter correct logins!");
    }
}

function undoMoveJS() {
    Module.ccall("undoMoveCPP", null, [], []);
    // Module.undoMove();
}

function makeMove(cell) {
    // alert("Cell clicked: " + cell.innerText);
    // Module._printArr();
    Module.ccall("movePlr", null, ["string"], [cell.id]);
    // Module.movePlr(cell.id);
}

function continueMulGame() {
    Module.ccall("continueMulGame", null, [], []);
    document.getElementById('cont-mul').style.visibility = "hidden";
}

// Load the initial content when the page loads
// window.onload = loadInitialContent;