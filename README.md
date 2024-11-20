### Bouncing Ball Game  

This is a simple 2D game created using Raylib in C. The goal is to control a paddle to keep the ball in play, bouncing it off walls, a red line, and the paddle itself. You start with three chances, and the game ends when all are lost.  

---

### Features  
- **Start Screen:** Displays the game title and a prompt to start.  
- **Paddle Control:** Move the paddle left or right using arrow keys to hit the ball.  
- **Collision Detection:** Ball bounces off walls, the paddle, and a red line at the top of the screen.  
- **Chance System:** You have three chances to prevent the ball from falling below the paddle.  

---

### How to Play  
1. Launch the game.  
2. Press **ENTER** to start.  
3. Use **LEFT** and **RIGHT** arrow keys to move the paddle.  
4. Keep the ball in play by bouncing it off the paddle.  
5. Avoid letting the ball fall below the paddle.  

---

### Requirements  
- Raylib Library  
- C Compiler  

---

### Controls  
- **LEFT Arrow Key:** Move the paddle left.  
- **RIGHT Arrow Key:** Move the paddle right.  
- **ENTER:** Start the game.  

---

### Compilation  
To compile the game, ensure Raylib is installed and use the following command:  
```bash  
gcc -o BouncingBallGame game.c -lraylib -lm -ldl -lpthread -lGL  
```  

---

### License  
This project is free to use and modify for personal or educational purposes.
