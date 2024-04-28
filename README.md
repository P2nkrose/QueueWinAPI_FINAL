<p align="center"><img alt="1" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/c5bc0826-039a-4ee4-9e7c-1abe378c5d7c"></p>

<h1>Window API 포트폴리오 : 메이플스토리</h1>

> Windows API를 활용한 2D Game Copy Project
<br>
<br>

<h2>프로젝트 영상</h2>

[![Video Label](http://img.youtube.com/vi/rJVViun10fQ/0.jpg)](https://youtu.be/rJVViun10fQ)

<br>
<br>

<h2>프로젝트 개요</h2>
<p align="center"><img width="550" alt="1" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/acf4979a-794d-4e8a-8009-2a0e76cc9914"></p>

```
2003년 출시된 메이플스토리의 모작으로, C++, Windows API를 활용해 제작했습니다.
개발자는 Collider Tool을 통해서 Platform의 지형을 직접 설정할수 있고, Monster Tool을 
이용해 몬스터를 해당 위치에 직접 배치할 수 있으며, Atlas Texture를 가져와 
애니메이션을 제작할 수 있는 기능을 추가했습니다.

직관적인 인터페이스를 통해 개발 효율성과 확장성을 증가시켰습니다.
또 원작 게임의 컨텐츠를 차용하여, 사용자는 스킬 사용을 통한 몬스터 사냥, 보스레이드 등
Ability의 성장을 경험할 수 있습니다.
```
<br>
<br>
<h2>프로젝트 설명</h2>
<b>게임 설명</b>
<p align="center"><img width="250" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/c304819c-d99c-4ee6-a649-4d82450dec05"></p>
<p align="center"><img width="610" alt="image" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/9b2cfa48-9c93-49c7-b89e-d59862b49f19"></p>
<br>
<b>프로젝트에 반영된 게임의 특징</b>
<br><br>

```
🍄 원작「메이플스토리」의 플레이 방식 / 컨텐츠를 재현
```



* 조작 방식
<img width="680" alt="image" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/84ac31b4-f29c-4900-a203-6ec197c59a08">

<br><br>

* 게임 플레이 및 매커니즘
```
메이플 스토리는 좌/우/점프키를 활용하는 2D 횡스크롤 게임입니다.

캐릭터가 갖고있는 고유 스킬을 활용하여 필드의 몬스터를 사냥합니다.
보스 스테이지는 다양한 보스의 스킬 패턴을 피하며 클리어를 할 수 있습니다.
```


* 캐릭터
```
게임 플레이에 사용되는 캐릭터는「시그너스」직업군의 소울마스터 입니다.
캐릭터는 하나만 선택할수 있으며, 5개의 스킬을 사용할 수 있습니다.
* 버프 스킬 / 기본 스킬 / 원거리 스킬 / 이동 스킬 / 광범위 스킬
몬스터와 보스 타격 시 각 스킬의 데미지별 이펙트를 구현하였습니다.

캐릭터는 기본이동 외 2단 점프 및 대시를 사용하여 이동할수 있습니다.
```

* 스테이지
```
원작 게임을 고증하여 게임 시작 시 Nexon 로고, 월드맵 선택 화면에서 서버를 선택할수 있습니다.

스테이지는 총 4개로 구성되어 있으며, 배경은 직업군의 시작마을인 「퀸스로드」입니다.
마을로 시작하여 몬스터 사냥터 스테이지, 보스로 이동하는 스테이지, 보스 스테이지로 구성됩니다.
```

* 몬스터 및 보스
```
원작 게임과 동일한 느낌을 주기 위하여「퀸스로드 수련의 숲」에 분포된 몬스터 2종을 그대로 구현 했습니다.
몬스터를 타격하면 각 스킬별 데미지 효과가 Animation으로 재생되며, 타격 sound 및 Effect를 구현 했습니다.
몬스터는 사망 시 Level에서 사망정보를 받아와 일정 시간 후 Respawn 됩니다.

보스는 시그너스이며, 4개의 스킬 패턴을 AI로 랜덤으로 자동 구현합니다.
* 원거리 스킬 / 전체 스킬 / 플레이어의 위치값을 받아와 해당 위치에 타격하는 유도 스킬
보스는 HP가 0이 되었을 시 사라지게 됩니다.
```



<br>
<h2>프로젝트 핵심 구현</h2>

```
🛠️ 손쉽게 Collider, 몬스터 배치가 가능한 EDIT TOOL
```
* Collider Edit Tool
<img width="680" alt="image" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/324d8d64-e774-4ea1-9145-4e39b3e6b9a4">

<br><br>

* Monster deploy Edit Tool
<img width="680" alt="image" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/4d6d4ae7-3bc1-4cca-8b50-9acb75ebb8cf">

<br><br>

* 조작 방식
<img width="601" alt="image" src="https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/96006bb4-946f-491d-8f5d-ee4281197ea5">



