# Pygame中的碰撞检测
## 使用pygame.sprite.groupcollide函数
groupcollide(groupa, groupb, dokilla, dokillb, collided=None) 
检测精灵组a和b中的精灵是否发生碰撞，若dokilla或dokillb为True则碰撞中对应精灵组的精灵被销毁
## 使用pygame.sprite.spritecollide函数
判断指定精灵和精灵组是否发生碰撞
```
enemies = pygame.sprite.spritecollide(self.hero, self.enemy_group, True)
if len(enemies) > 0:
    self.hero.kill()
    self.__game_over()
```