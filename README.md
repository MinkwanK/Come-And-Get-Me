 # Horror Game
**아예 싹 바꿀 예정<br>
기능 구현 위주의 공포게임<br>
사람이 귀신을 피해 저택을 탈출하는 게임을 만들 예정**


## 게임 개요
- 개요: 사이비 신도들의 집에 침입한 기자의 스토리를 게임으로 구현
- 개발 도구: 언리얼엔진5, Rider
- 개발 언어: C++
- 개발 인원: 1인개발
- 장르: 공포, RPG, 1인칭
- 게임 소개: 플레이어는 기자이다. 사이비신도들이 있는 집을 탐색하며, 기사에 낼 수 있는 증거들을 수집한다. 증거들을 모아 신도들을 피하여 집을 탈출하는 것이 목표. 
             기자는 총 및 근접무기를 이용하여 전투를 할 수 있다.

## 구현목표
### Player 조작
 - ~~상하좌우 이동~~
 - ~~점프~~
 - ~~앉기~~ (Left Ctrl)
 - ~~걷기~~
 - ~~뛰기(Shift)~~
 - 손전등 (F 키)
 > SpotLightComponent를 FPS 카메라에 부착. Player가 바라보는 시점에 따라 카메라가 돌아간다.
 > Player의 상태를 나태는 열거형 enum 적용
 
 
 ### Player의 시점
- FPS 카메라
> Player Mesh의 Head에 소켓을 추가하여, Camera 를 부착

### Player 아이템 시스템
- 권총 장착
- ~~권총 AimOffset 적용 ~~

 
 ### Player의 체력
 - 체력 구현
 
 ### 신도의 Player 공격
 - 추가 예정


### 신도 NPC 
  - Sight Sense 부여
  - Hearing Sense 부여
  >  Player의 소리 인지시 소리가 난 Location 갱신 -> 소리가 난 TargetLocation으로 이동
  > 특정 소리마다 다른 ManRange 값을 부여하여, 자연스러운 소리 인지를 구현
  - ~~신도에게 순찰 구현~~
  - 신도는 Player을 찾기 위해 집을 순찰하며 수색해야 한다. <br>
   >  무작위 이동 방식: 랜덤하게 주어진 타겟 포인트를 방문한다. <br>문제점 -> 어색한 순찰이고, 직전에 방문했던 타겟 포인트를 재방문하는 어색한 상황이 펼쳐진다.<br><br>
   >  직전 방문 기억 방식: 직전에 방문한 타겟 포인트는 방문하지 않아, 그나마 덜 어색해졌다. <br>문제점 -> 타겟 포인트의 수가 적을때는 어색함이 덜하지만, 타겟 포인트의 양이 많아지면 문제가 발생할 것으로 예측된다. 또한, 순찰을 돌때 효율성을 위해 무조건 인코스로 돌게 된다.
   
  - ~~신도에게 Player 추적 구현~~
  > Player에게 AIPerceptionStimuliSourceComponent 부착 -> register sight <br>
  > Player를 Perception 하면 TargetPlayer 블랙보드 키에 플레이어를 업데이트 <br>
  > 신도는 순찰을 돌다가 플레이어를 발견하면, Player를 추격한다. <br>
  


### UI
- 메인 화면 UI
 > 게임 시작, 계속하기, 게임 종료 
- 스테이지 선택 UI
 > 스테이지 선택, 스킬, 뒤로가기
- 게임 오버 UI
 > 재시작, 스테이지 선택
 > 공포 화면 연출, 공포 사운드
 
### 사운드
- 플레이어
> 발소리, 공격소리
- 신도
> 발소리, 웃음소리
> 사용자를 놀래킬 만한 소리가 필요하다.적의 거리별 사운드 감쇄 효과 적용
- 게임 오버 사운드



## 배운 점
AIController 소스파일에 AIPerception Component를 생성하면, 그 AIC를 사용하는 AI들은 Perception 을 가지게 된다. 예시로 AIC에 Eye Perception 을 주고 AI에 AIC를 적용하면 Eye Perception 을 가지게 된다.

소리를 낼려면 emittercomponent 가 필요하다. float volume 만큼의 make noise 사용 

시야와 청각 두개를 동시에 쓸 때, Dominant Senese를 null로 

애니메이션 몽타주가 제대로 재생이 되지 않을때, Blend Option에 Blend in과 Blend out을 0.0으로 
Blend Time이란 Pose A에서 Pose B로 바꾸는 시간


## 피드백
0.1v
손전등이 있으면 좋겠다.
삐에로에게 발각되면 계속 쫓아온다. 숨는 곳이 있으면 좋겠다.






