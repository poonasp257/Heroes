# Graduate Project For Game Software Major

## Introduction  
+ Title: Heroes  
+ Genre: MMORPG  

## Game Design

## Tech
### Client
* Language: C#  
* Engine: Unity  

### Server
* OS: Windows  
* Language: C++, Json  
* Library: rapidjson  
* ETC: MultiThread programming, IOCP  

### DB
* MySQL, MongoDB

## Develop
### 1. 2019년 9월 25일 작업
[![Video Label](https://img.youtube.com/vi/rsNnGrNGuIc/0.jpg)](https://youtu.be/rsNnGrNGuIc)

### Impelemtation
1. 플레이어 3인칭 카메라  
  1) 카메라와 오브젝트 충돌 처리  
  2) 대상 오브젝트를 Follow하는 기능  
2. 플레이어 이동  
  1) 카메라가 바라보는 방향으로 캐릭터 이동  
  2) 캐릭터 애니메이션  
3. 맵  
  1) 마을 맵 구성  
  
### 2. 2019년 10월 2일 작업
[![Video Label](https://img.youtube.com/vi/PKGwDd61of8/0.jpg)](https://youtu.be/PKGwDd61of8)

### Impelemtation
1. 플레이어 공격  
  1) 마우스 이벤트에 따라 설정된 애니메이션 실행  
  2) 공격 콤보 시스템 구현  
2. 맵  
  1) 사막 맵 구성 (오브젝트 미배치)  
  
### 3. 2019년 11월 14일 작업
[![Video Label](https://img.youtube.com/vi/m8c_W4b1czg/0.jpg)](https://youtu.be/m8c_W4b1czg)

### Impelemtation
1. C#, C++ Marshaling
  1) C++ 서버와 C# 클라이언트 간에 패킷 주고받을 수 있도록 구현
2. 타이틀 씬
  1) 로그인 기능 구현(서버 측에서 DB 사용하지 않고 있음..매직코드로 작성) 
3. 로딩씬
  1) Progress bar 연출 구현

### Remark
서버 측에서 클라이언트로 전송하는 패킷을 수신받은 패킷으로 처리하는 버그가 있었다.   
분명 클라이언트 측에서는 하나만 보냈는데 수신받은 패킷은 2개...  
쓰레드가 하나가 아니라 디버깅도 만만치 않았다...  

### To do
1. 쓰레드 관리, 동기화에 대한 처리
2. 현재 new 키워드를 이용한 동적할당 부분을 smart pointer로 대체
3. 패킷 수신 시 함수 테이블로 처리
4. DB 추가

