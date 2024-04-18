![image](https://github.com/P2nkrose/WinAPI_MapleStory/assets/124218203/021ef96c-90de-4a48-b151-9151451aa1d1)

<h1>Copycat’s Maple Story</h1>

> Windows API를 활용한 2D Game Copy Project


### 프로젝트 개요

---

|  📋 프로젝트 이름 | Copycat’s Maple Story |
| --- | --- |
|  🗓️ 프로젝트 기간 | 2024.03-2024.04 |
|  🛠️ 개발 환경 및 언어 | C++
||Windows API
||Visual Studio 2022 |
| 👥 멤버 | 김도규  @부트 스프링   |

```
2003년 출시된 메이플스토리의 모작으로, C++, Windows API를 활용해 제작했습니다.
개발자는 Collider Tool을 통해서 Platform의 지형을 직접 설정할수 있고, Monster Tool을 
이용해 몬스터를 해당 위치에 직접 배치할 수 있으며, Atlas Texture를 가져와 
애니메이션을 제작할 수 있는 기능을 추가했습니다.

직관적인 인터페이스를 통해 개발 효율성과 확장성을 증가시켰습니다.
또 원작 게임의 컨텐츠를 차용하여, 사용자는 스킬 사용을 통한 몬스터 사냥, 보스레이드 등
Ability의 성장을 경험할 수 있습니다.
```



### 프로젝트 설명

---

**게임 설명**


| 게임명 | 메이플스토리 |
| --- | --- |
| 개발 / 출시 | 위젯스튜디오 (넥슨) / 2003년 4월 29일 |
| 플랫폼 | PC (Microsoft Windows) |
| 장르 | 2D 횡스크롤 MMORPG |

**프로젝트에 반영된 게임의 특징**

- 게임 플레이 및 매커니즘

```
메이플 스토리는 좌/우/점프키를 활용하는
2D 횡스크롤 게임입니다.

캐릭터가 갖고있는 고유 스킬을 활용하여
필드의 몬스터를 사냥하며, Exp를 얻게 됩니다.
Exp가 일정게이지까지 오르면 레벨업을 하며
보스 스테이지는 다양한 보스의 패턴을 피하며
클리어를 할 수 있습니다.
```

- 스테이지

```
원작 게임을 고증하여 게임 시작 시 Nexon 로고,
월드맵 선택 화면에서 서버를 선택할수 있습니다.

스테이지는 총 4개로 구성되어 있으며,
배경은 직업군의 시작마을인 「퀸스로드」입니다.
마을로 시작하여 사냥터 스테이지, 보스로 이동
하는 스테이지, 보스 스테이지로 구성됩니다.
```

- 캐릭터

```
게임 플레이에 사용되는 캐릭터는
「시그너스」직업군의 소울마스터 입니다.
캐릭터는 하나만 선택할수 있으며, 5개의 스킬을
사용할 수 있습니다.
* 버프스킬/기본스킬/원거리스킬/이동스킬/필살

캐릭터는 기본이동 외 2단 점프 및 대시를
사용하여 이동할수 있습니다.
```

- 몬스터 및 보스

```
원작 게임과 동일한 느낌을 주기 위하여
「퀸스로드 수련의 숲」에 분포된 몬스터 2종을
그대로 구현하였습니다.
몬스터가 죽으면, 일정 시간 후 Respawn 되며,
캐릭터는 Exp를 획득할 수 있습니다.

보스는 시그너스이며, 4개의 패턴을 구현합니다.
```


**프로젝트 설명**

<aside>
🛠 손쉽게 Collider, 몬스터 배치가 가능한 Edit Tool

</aside>

- Collider Edit Tool
    
    
    | 개요 | 맵을 구성하는 Platform과 Rope, Portal 등을 스테이지 별 알맞는               에셋에 따른 Spawn Position을 지정할 수 있는 모드 |
    | --- | --- |
    | 세부 기능 | - Level 내 Background Object에 맞는 Platform, Rope 및 기타 Collider를              Drag &  Drop을 통한 편리한 위치 지정 |
    - Collider Edit Tool 구현
        
        [동영상 첨부]
        

- Monster deploy Edit Tool
    
    
    | 개요 | 해당 Level에 맞는 Field의 몬스터를, 마우스 클릭으로 deploy 하는 모드 |
    | --- | --- |
    | 세부 기능 | - Level 내 Background Object에 맞는 몬스터의 위치를, 마우스클릭으로   해당 MousePos의 위치로 몬스터가 Spawn되게 지정 |
    - Monster deploy Edit Tool 구현
        
        [동영상 첨부]
        

<aside>
🍄 원작 ‘메이플스토리’의 플레이 방식 / 컨텐츠를 재현

</aside>

- 조작 방식
    
    
    | 상호작용 | MOVE | DOWN / ATTACK | ROPE |
    | --- | --- | --- | --- |
    | 키보드 | ⬅️ ➡️ | ⬇️ + CTRL | ⬆️ ⬇️ |
    | 상호작용 | SKILL | (DOUBLE)  JUMP | JUMP DASH |
    | 키보드 | A S D F G  | SPACE BAR  | SPACE BAR  + ⬅️ ➡️ + SPACE BAR  |
