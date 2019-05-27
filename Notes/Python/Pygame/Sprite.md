# 精灵和精灵组
## 精灵
直接控制图像的加载，位置变化，图像刷新很繁琐，pygame提供了sprite类抽象游戏中的角色简化开发。使用需要派生并重写update()方法
### 1. 重要属性
-   image 图像数据
-   rect 位置
### 2. 重要方法
-   update() 更新精灵位置
-   kill() 从所有组删除
 
## 精灵组
### 1. 构造函数
\_\_init\_\_(self,*精灵)
### 2. 方法
-   update(*args) 让组中所有精灵调用update()方法
-   draw(Surface) 将组中精灵的image绘制到Surface的rect位置
-   add(*sprite) 添加精灵
-   sprites() 返回组中精灵列表
## 示例代码
### 1. 精灵类
```
import pygame
 
class GameSprite(pygame.sprite.Sprite):
    def __init__(self,image_name,speed=1):
        super().__init__()
        self.image = pygame.image.load(image_name)
        self.rect = self.image.get_rect()
        self.speed = speed
 
    def update(self, *args):
        self.rect.y += self.speed
```
### 2. 游戏循环
```
import pygame
from plane_sprites import *
 
pygame.init()
screen = pygame.display.set_mode((480, 700))
 
bg = pygame.image.load("./images/background.png")
screen.blit(bg, (0, 0))
clock = pygame.time.Clock()
fps = 60
 
airplane = pygame.image.load("./images/me1.png")
airplane_rect = pygame.Rect(150, 500, 102, 126)
screen.blit(airplane, airplane_rect)
 
enemy = GameSprite("./images/enemy1.png")
enemy1 = GameSprite("./images/enemy1.png",speed=2)
enemy_group = pygame.sprite.Group(enemy,enemy1)
 
 
while True:
    clock.tick(fps)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
 
    screen.blit(bg, (0, 0))
    airplane_rect.y = airplane_rect.y - 1 if airplane_rect.bottom > 0 else 700
    screen.blit(airplane, airplane_rect)
 
    enemy_group.update()
    enemy_group.draw(screen)
 
    pygame.display.update()
 
```