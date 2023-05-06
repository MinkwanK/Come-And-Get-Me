 # Unreal FPS 게임



## 게임 개요

- 장르: FPS
- 소개: NPC의 플레이어 인지 및 추격, 아이템 획득 및 사격 시스템을 구현한 게임



## 배운 점
AIController 소스파일에 AIPerception Component를 생성하면, 그 AIC를 사용하는 AI들은 Perception 을 가지게 된다. 예시로 AIC에 Eye Perception 을 주고 AI에 AIC를 적용하면 Eye Perception 을 가지게 된다.

소리를 낼려면 emittercomponent 가 필요하다. float volume 만큼의 make noise 사용 

시야와 청각 두개를 동시에 쓸 때, Dominant Senese를 null로 

애니메이션 몽타주가 제대로 재생이 되지 않을때, Blend Option에 Blend in과 Blend out을 0.0으로 
Blend Time이란 Pose A에서 Pose B로 바꾸는 시간










