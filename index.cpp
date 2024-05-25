#include <Game.h>
#include <Multiplayer.h>
#include <AIGame.h>
#include <iostream>
using namespace std;

// struct MyObject {
//     int id;
//     string name;
//     operator json() {
//             return json{{"id", id}, {"name", name}};
//         }
// };

// void processTextboxContent() {
//     // const char* content = getTextBoxContent();
//     // Now you have the content in C++ and can process it
//     // cout << "Content received: \n" << content << endl;
// }

// EM_JS(const char*, get_js_string, (), {
  // Assuming there's a JavaScript function or variable `getMyString`
  // that returns the string you want to pass to C++
  
  // return getTextBoxContent();
// });

// extern "C" {
//     EMSCRIPTEN_KEEPALIVE void sendTextToCpp() {
//         EM_ASM({
//             let text = document.getElementById('text-input').value;
//             Module.ccall('receiveTextFromJS', // Name of the C++ function
//                  null,                // Return type
//                  ['string'],          
//                  [text]);             // Arguments
//         });
//     }

//     EMSCRIPTEN_KEEPALIVE void receiveTextFromJS(const char* text) {
//         cout << "Received text from JS: " << text << endl;
//         string str = text;
//         cout << "Length of this text is: " << str.length() << endl;
//         // Handle the text as needed
//     }
// }

// extern "C" {
//   EMSCRIPTEN_KEEPALIVE void sendArrToCpp() {
//     cout << "Sending array..." << endl;
//     EM_ASM({
//       var jsArray = ([10, 2.30, 30, 40, 50]);

//     // Allocate memory in the WebAssembly module's linear memory to store the array
//     var arrayPtr = _malloc(jsArray.length * 8); // Assuming 4 bytes per int (change as needed)

//     // Copy the JavaScript array elements into the allocated linear memory
//     for (var i = 0; i < jsArray.length; i++) {
//         setValue(arrayPtr + (i * 8), jsArray[i], 'double'); // Assuming 32-bit integers
//     }

//     // Now, you can call a C++ function and pass the pointer and the array length
//     // For example, if you have a C++ function named receiveArrayFromJS defined as:
//     // extern "C" void receiveArrayFromJS(int* array, int length);
//     Module._receiveArrayFromJS(arrayPtr, jsArray.length);

//     // Optionally, free the allocated memory if it's no longer needed
//     _free(arrayPtr);
//     });
//   }

//   EMSCRIPTEN_KEEPALIVE void receiveArrayFromJS(double* array, int length) {
//     cout << 1 << 45.2 << endl;
//     cout << array[0] << " " << array[1] << " " << array[2] << endl;
//   }
// }

// extern "C" {
//     EMSCRIPTEN_KEEPALIVE void open() {
//         EM_ASM({
//             // Fetch the file using JavaScript
//             fetch('./db.json').then(response => response.arrayBuffer()).then(data => {
//                     // Convert the fetched file into an Emscripten FS object
//                     FS.writeFile('/db.json', new Uint8Array(data));
//                     // Now you can call your C++ function that reads this file
//                     Module.ccall('openAndReadFile', null, ['string'], ['/db.json']);
//                 });
//         });
//     }
//     EMSCRIPTEN_KEEPALIVE void openAndReadFile(const char* filename) {
//         ifstream file(filename);
//         if (file.is_open()) {
//             json j = json::parse(file);
//             string js = j.dump(4);
//             cout << js << endl;
//             file.close();
//         } else {
//             cout << "Unable to open file" << endl;
//         }
//     }
//     EMSCRIPTEN_KEEPALIVE void mainFunc() {
//         open();
//     }
// }

// int main() {
//     cout << "Hello" << endl;
//     // Game().run();

//     // MyObject mobj = {1, "Test Object"};
//     // json j = mobj;
//     // string jsonStr = j.dump(4); // Serialize to JSON string
//     // const char* c_str = jsonStr.c_str();

//     // Pass the JSON string to JavaScript
//     // EM_ASM({
        
//     // });

//     return 0;
// }

// extern "C" {
//     EMSCRIPTEN_KEEPALIVE void mainFunc() {
//         Game().run();
//         cout << "Running" << endl;
//     }
// }

Game* G = nullptr;
Multiplayer* Mul = nullptr;
AIGame* AI = nullptr;
Player* plr1 = nullptr;
Player* plr2 = nullptr;

extern "C" {
  EMSCRIPTEN_KEEPALIVE void createGame() {
      G = new Game();
      cout << "Game created" << endl;
  }

  EMSCRIPTEN_KEEPALIVE void createMultiplayer() {
      Mul = new Multiplayer();
      cout << "Multiplayer created" << endl;
  }

  EMSCRIPTEN_KEEPALIVE void createAIGame() {
      AI = new AIGame();
      cout << "AI Game created" << endl;
  }
}