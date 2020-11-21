# Graduate Project For Game Software Major

## Introduction  
+ Title: Heroes  
+ Genre: MMORPG  
+ Platform: PC

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
* MSSQL(+ODBC), MongoDB

## Develop
### 1. 2019년 9월 25일 작업
[![Video Label](https://img.youtube.com/vi/rsNnGrNGuIc/0.jpg)](https://youtu.be/rsNnGrNGuIc)

### Impelemtation
1. 플레이어 3인칭 카메라  
  1-1. 카메라와 오브젝트 충돌 처리  
  1-2. 대상 오브젝트를 Follow하는 기능  
2. 플레이어 이동  
  2-1. 카메라가 바라보는 방향으로 캐릭터 이동  
  2-2. 캐릭터 애니메이션  
3. 맵  
  3-1. 마을 맵 구성  
  
### 2. 2019년 10월 2일 작업
[![Video Label](https://img.youtube.com/vi/PKGwDd61of8/0.jpg)](https://youtu.be/PKGwDd61of8)

### Impelemtation
1. 플레이어 공격  
  1-1. 마우스 이벤트에 따라 설정된 애니메이션 실행  
  1-2. 공격 콤보 시스템 구현  
2. 맵  
  2-1. 사막 맵 구성 (오브젝트 미배치)  
  
### 3. 2019년 11월 14일 작업
[![Video Label](https://img.youtube.com/vi/m8c_W4b1czg/0.jpg)](https://youtu.be/m8c_W4b1czg)

### Impelemtation
1. C#, C++ Marshaling
  1-1. C++ 서버와 C# 클라이언트 간에 패킷 주고받을 수 있도록 구현
2. 타이틀 씬
  2-1. 로그인 기능 구현(서버 측에서 DB 사용하지 않고 있음..매직코드로 작성) 
3. 로딩씬
  3-1. Progress bar 연출 구현

### Remark
- 서버 측에서 클라이언트로 전송하는 패킷을 수신받은 패킷으로 처리하는 버그가 있었다.   
분명 클라이언트 측에서는 하나만 보냈는데 수신받은 패킷은 2개...  
쓰레드가 하나가 아니라 디버깅도 만만치 않았다...  

### To do
1. 쓰레드 관리, 동기화에 대한 처리  
2. 현재 new 키워드를 이용한 동적할당 부분을 smart pointer로 대체  
3. 패킷 수신 시 함수 테이블로 처리  
4. DB 추가  

### 4. 2019년 11월 22일 작업
[![Video Label](https://img.youtube.com/vi/5CTqVJA7kb4/0.jpg)](https://youtu.be/5CTqVJA7kb4)

### Impelemtation
1. 쓰레드 동기화 처리  
  1-1. std lock_guard와 mutex를 이용해서 스코프 락 사용하여 동기화 처리  
  1-2. 쓰레드 작업 큐 만들었음. 가끔씩 쓰레드가 죽는 상황이 발생... 라이브러리 사용하는게 나을수도  
2. 패킷 수신  
  2-1. 함수 테이블을 사용한 패킷 처리  
3. 채널 선택 화면  
  3-1. 유저 분산을 위한 채널 서버를 선택할 수 있는 화면 추가  
  //아직 채널 분산을 구현하지는 않았음
4. 캐릭터 선택 화면  
  4-1. 서버로부터 Account에 해당하는 캐릭터 정보들을 불러와 화면에 띄움. 클래스, 레벨, 캐릭터명, 마지막 접속 위치 등을 보여줌.  
  //캐릭터 생성, 삭제, 이전 화면 등 상호작용 버튼은 미구현  
  //캐릭터 선택 시 해당 캐릭터의 모델을 화면 중앙에 띄울 예정..  

### Remark
- DB 쿼리문을 구현하기가 만만치 않아 DB를 연결하지 못해서 서버측에서 매직 코드로 처리하고 있다...

- 채널과 캐릭터 선택 화면의 UI는 검은사막을 레퍼런스로 하였음.

### To do
1. DB 추가
2. 유저 접속
3. 플레이어 이동 동기화 구현

### 5. 2019년 11월 29일 작업
[![Video Label](https://img.youtube.com/vi/p6aRfXLTfC0/0.jpg)](https://youtu.be/p6aRfXLTfC0)

### Fix
1. 쓰레드 작업 큐 동기화 문제 수정
2. Lobby Manager 클래스를 세분화해서 각각의 씬에 맞게 수정

### Impelemtation
1. 유저 접속  
  1-1. Account Id와 선택하여 접속한 캐릭터 정보 매핑한 Player Table 구현  
  1-2. 접속 시 서버로부터 Player Table 정보를 받아오고, 이를 바탕으로 캐릭터 생성. 다른 클라이언트 측에서는 브로드캐스팅으로 받은 새로운           플레이어 정보를 자신의 Player Table을 갱신하고 캐릭터 생성  
      // Player가 접속 종료에 대한 처리는 아직 하지 않았음.  
2. 플레이어간 이동 동기화  
  1-1. 플레이어 입력에 따라 캐릭터의 Transform 정보가 바뀌면 서버에 전달하고 서버는 이를 브로드캐스팅..

### Remark
- 씬 전환 시 이전 씬에서 서버로부터 받은 데이터를 전달하는 과정이 필요했다. 
>1. DontDestroyOnLoad 
>2. static 혹은 singleton 클래스에 데이터 저장
두 가지 해결책이 있었는데, 1번으로 구현하다보니 스크립트에 해당 스크립트와 관련 없는 코드 블록들이 등장해서
상당히 지저분해 보였음. 그래서 2번으로 다시 구현...

- 처음에는 Player Table의 key 값을 서버측 Session Id나 CharacterId로 매핑 시켰었는데 만약, 다른 클라이언트가 같은 Account에 접속한다면..? 그래서 Account Id 값으로 변경. 그런데, Session이 비정상적으로 끊겼을 때 Player Table을 갱신하고 이에 따른 처리를 해야하는데, IOCP 서버에서 Session이 끊기면 GetQueuedCompletionStatus로 얻어낸 transfer size 값이 0으로 처리되는 부분은 확인했으나 Main Process 측에서는 이를 어떻게 확인을 해야할까...

- 유저의 접속, 이동 등의 정보를 다른 클라이언트에게도 전달하기위해서 브로드캐스팅을 할 필요가 있었다. 그래서 UDP 소켓을 통해서 브로드캐스팅을 구현하려고 했으나, 다른 서버 프레임워크나 구글링을 해본 결과 라우터의 성능이좋아져서 UDP가 아닌 TCP로도 충분히 빠르게 실시간으로 패킷을 주고받는 것이 가능하다는 것을 알았다. 다만, 네이글 알고리즘으로 인해 패킷 지연이 발생할 수 있는 상황을 예상해서 TCP 소켓에 NO_DELAY 옵션을 추가했다. 로컬에서 실험했을 땐 아무 문제없이 빠르게 동작했다. 다만, 플레이어 입력을 받을 때마다 패킷을 보내고 있어서 접속자가 많아지거나 로컬이 아닌 환경에서 구동한다면 레이턴시가 발생할 것으로 예상된다. 현재로서는 이에 대한 해결책으로 데드 레커닝 기법이 가장 적합할 것 같다.

- 공격이나 기타 액션에 대한 처리도 하려고 했으나, 처음에 클라이언트 구현할 때 스크립트를 분리하지 않고 구현한 탓에 로직이 복잡해서 스크립트를 분리하고 로직을 바꿀 필요가 있을 것 같다.

### To do
1. DB 추가
2. 동시 접속 방지
3. 접속 종료 처리
4. 공격 등 기타 액션에 대한 처리
5. 인게임 UI(레벨, 체력, 마나, 미니맵, 경험치, 가문명, 캐릭터명 등)
6. 몬스터 스폰
7) 더미 클라이언트
8) 메모리릭, 덤프 클래스

### 6. 2019년 12월 3일 작업
[![Video Label](https://img.youtube.com/vi/VyQ3YxeMtLo/0.jpg)](https://youtu.be/VyQ3YxeMtLo)

### Impelemtation
1. In Game UI  
  1-1. 플레이 중인 캐릭터의 UI 구현. HP와, MP바의 경우 최대 HP, MP의 값과 현재 HP, MP 값의 퍼센티지로 계산하여 표시하며 표시하는 화살표를          만들어서 직관적인 UI 구성  
  1-2. 미니맵 구현. 캐릭터의 위치를 화살표 모양으로 보여주고, 캐릭터가 바라보는 방향으로 표시. 다른 유저는 사각형으로 표시.  
  1-3. 가문명, 캐릭터명 해당 캐릭터 위에 표시. 거리가 멀어지면 서서히 UI를 지움. 차후 LOD도 구현하면 좋은듯  
 
### To do
1. DB 추가
2. 동시 접속 방지
3. 접속 종료 처리
4. 공격 등 기타 액션에 대한 처리
5. 몬스터 스폰
6) 더미 클라이언트
7) 메모리릭, 덤프 클래스

### 7. 2019년 12월 8일 작업
[![Video Label](https://img.youtube.com/vi/HmW7MBP-Scc/0.jpg)](https://youtu.be/HmW7MBP-Scc)

### Impelemtation
1. 분산서버 구현  
  1-1. 간단한 서버 to 서버 1:1 기반의 소켓통신을 위한 클래스 구현.  

2. 데이터베이스 연동  
  2-1. ODBC API를 이용해서 MSSQL에 접속.  
  2-2. 로그인, 회원가입, 캐릭터 생성, 캐릭터 삭제, 캐릭터 정보 등 쿼리문 작성  

3. 로그인, 회원가입 구현  
  3-1. DB를 연동한 로그인, 회원가입 구현. 특수문자, 글자 수 제한 등 예외 사항에 대한 처리 미흡  

4. 캐릭터 생성, 삭제 구현  
  4-1. 캐릭터 생성 씬 구성. 차후 UI 리소스를 찾아서 추가하도록 하겠음.   
  4-2. 캐릭터 선택창에서 캐릭터 삭제 요청 구현.  

### Remark
RDBMS로 MySQL을 선택하여 프로젝트를 구상했었으나, MySQL의 경우 Connector 라이브러리를 별도로 설치해야해서 MSSQL로 진행했다. 서버 사이드는 C++기반이므로 ODBC나 OLEDB를 선택해야 했는데 ODBC는 초기에 서버마다 DSN 설정을 해야한다는 불편함이 있고 (SQLDriverConnect 함수를 쓰면 DSN 설정을 하지 않아도 된다고는 하나 시도해보다가 일단 접어뒀다.) 반면, OLEDB는 DSN 설정이 필요없고 SQL 뿐만 아니라 NoSQL에도 연결할 수 있다는 장점과 사용하기에 편리하다는 사람들의 의견이 많았다. 다만, OLEDB는 윈도우 환경에서만 구동된다는 단점이 있어서 각각의 장단점이 있어 일단은 ODBC를 발전시킨 것이 OLEDB이니 ODBC를 먼저 사용해보고 부족하다면 OLEDB로 바꿔서 사용해도 좋을 것 같아 ODBC로 선택했다. 
쿼리문 작성에 익숙치 않아서 구글링하면서 쿼리문 예제를 찾느라 시간이 좀 걸렸다..스키마도 어떻게 만들어야할지 감이 안와서 일단은 하나의 테이블로 만들어서 작성했다. ODBC에서 SQL 쿼리 결과를 SQLBindCol로 열에 대한 바인딩으로 값을 가져왔는데 자꾸 NULL 값이 나와 왜 그런가 했더니   데이터 타입에 대한 인자로 SQL_C_SHORT를 넘겨줘야 했는데 SQL_SHORT를 넘겨줘서 데이터 형식 불일치로 NULL 값을 가져온 것이였다...
