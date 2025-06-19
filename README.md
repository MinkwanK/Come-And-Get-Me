# 🎯 Unreal FPS Game

## 📌 개요

- **장르:** 1인칭 슈팅 (FPS)  
- **설명:**  
  플레이어를 인식하고 추격하는 NPC AI, 아이템 획득, 사격 기능 등을 구현한 언리얼 엔진 기반 FPS 게임입니다.

## 🧠 주요 학습 내용

- `AIController`에 `AIPerceptionComponent`를 추가하면, 해당 컨트롤러를 사용하는 AI는 **Perception 기능**을 갖게 됩니다.  
  예: 시각 감지를 설정하면 AI가 플레이어를 **시야로 인식**할 수 있습니다.

- 소리를 감지하려면 `EmitterComponent`가 필요하며, `MakeNoise(float Volume)` 함수를 사용해 AI가 **청각 이벤트**를 감지할 수 있습니다.

- 시각과 청각을 **동시에 사용할 경우**, `Dominant Sense`를 `None`(또는 `Null`)으로 설정해야 모든 감각이 동등하게 처리됩니다.

- **애니메이션 몽타주가 재생되지 않을 경우**:  
  `Blend In`과 `Blend Out` 값을 `0.0`으로 설정하여 자연스럽게 동작하도록 할 수 있습니다.  
  → `Blend Time`은 포즈 A에서 B로 전환되는 시간입니다.
