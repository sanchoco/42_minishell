## Bash Shell 재구현


**구현한 기능:**

- 새 명령을 기다릴 때 프롬프트 표시
- bash와 같이 올바르게 실행 파일을 찾고 실행(환경 변수 또는 상대, 절대경로를 기반)
- 동작하는 기능 목록
    1. echo와 -n 옵션
    2. cd 와 절대 경로 혹은 상대 경로
    3. pwd
    4. export
    5. unset
    6. env
    7. exit
    8. ; bash와 같이 명령을 분리
    9. ' 와 " bash와 같이 작동(여러줄은 x)
    10. 리다이렉션 '<' '>' '>>'
    11. 파이프 | bash와 같이 동작
    12. 환경 변수 ($ 뒤 문자) bash와 같이 동작
    13. $? bash와 같이 동작
    14. ctrl-C, ctrl-D, ctrl-\ 

---

### 해석

1. 환경 변수는 int main(int argc, char **argv, char **envv)에서 이중 포인터 형태의 envv인자로 받아 올 수 있게 된다.
2. execve(char* 실행파일명, char **옵션, char **환경변수)
    - 외부 프로그램을 실행시키는 명령어, 실행파일 명은 경로(ls는 /bin/ls)까지 입력해야 하며 정상 실행 시 프로세스가 종료된다. 실패시 프로세스는 유지되며 execve 다음 명령어가 실행이 됨.
3. fork()는 자식 프로세스를 생성하는 명령어이다.
반환값으로 부모 프로세스는 자식의 PID값을, 자식 프로세스는 0을 갖게 된다.
4. Ctrl-C와 Ctrl+\는 signal 함수를 통해 이벤트 처리가 가능하며 선언할 때부터 감지할 수 있게 된다. signal(SIGINT, 이벤트핸들러)와 같은 형태를 지니고 있으며 이벤트 핸들러는 void형 함수로 만들면 된다.
5. dup, dup2 함수는 리다이렉션과 파이프라인 처리를 위해 필요하다.
6. strerror 함수는 정수형으로 된 에러넘버를 메세지로 바꿔주는 함수이다.
7. 어떤 명령어를 실행했을 때와 실행파일을 직접 실행시켰을 때 출력되는 메세지가 다름. asdfadsf > command not found, ~/abc.c > No such file or directory
    - 경로를 입력했을 때는 바로 실행, 경로가 없는 명령어를 작성했을 때 PATH에서 찾는 듯..
8. echo $? 을 했을 때 마지막으로 실행한 명령의 리턴값(exit값)을 볼 수 있음.

### 프로그램 실행 과정

1. **준비**
    - main함수의 세번째 매개변수를 통하여 시스템 환경변수 불러오기
    - 불러온 시스템 환경변수를 char** 자료형으로 복제(unset과 export에서 자유롭게 사용하기 위함)
    - 기본적인 쉘 프롬프트 출력
2. **입력 받기**
    - get_next_line 함수의 FD를 STDIN_FILENO으로 설정하여 한줄씩 표준입력 받을 수 있도록 함.
3. **입력받은 문자열 파싱**
    - 아래 변수를 포함하는 구조체를 생성하고 링크드리스트로 구성
    - char **program : 명령어와 인자를 담음 ex) {"ls", "-al", NULL}
    - int flag : 세미콜론이나 파이프, 리다이렉션의 정보를 담음.

          ; 또는 문자열 끝 = 0,   | = 1, > = 2, >> = 3

    - 플래그로 끝날 경우 리스트의 새로운 노드를 만들어 명령어, 인자를 담는 구조체를 만들고 끝날 때까지 반복.
4. **명령어 처리**
    - 하나의 명령어 세트를 처리하기 전 $로 시작하는 환경변수 문자를 치환
    - 리스트에 담긴 구조체를 불러오며 플래그 조건에 따라 다르게 처리
    - **기본 처리(세미콜론이거나 명령어만 있을 경우)**
        1. 내부 명령어(echo, cd, export 등)일 경우 만들어둔 함수 실행
        2. 외부 명령어(ls, cat, ps 등)일 경우 fork함수로 자식 프로세스를 만들고 execve함수를 이용하여 실행
    - **리다이렉션( >, >>, < )**
    ```
        1.  '>', '>>', '<'에 따라 open함수에서 파일여는 권한을 설정하고 실행하여 FD를 불러옴
        2. 불러온 FD를 dup2함수를 통해 출력(명령어)을 입력(파일 쓰기)으로 연결
        3. \> file > file과 같이 리다이렉션이 여러 개 나올 경우, 재귀를 통하여 해당 과정을 반복
        4. 기본 처리 과정과 똑같이 명령어를 실행. 
        5. 리다이렉션이 모두 끝나면 dup2함수를 통해 처음의 FD으로 변경 
    ```
    - **파이프( | )**
```
        1. 파이프를 사용하는 개수만큼 파이프FD를 저장할 int** 배열을 만든다.
        2. 파이프의 갯수만큼 pipe()함수를 실행하고 파이프FD를 배열에 저장
        3. 명령어의 갯수만큼 반복문을 돌며 fork()함수를 통해 동등한 위치의 하위 프로세스를 생성
        4. 해당 명령어의 입력을 이전 명령어의 파이프FD로 바꾸고 출력을 다음 명령어의 파이프FD로 변경, 쓰지 않는 파이프는 닫아줌.
        5. 기본 처리 과정와 똑같이 실행
        6. 부모 프로세스는 자식 프로세스가 종료될 때까지 대기
```
5. **종료**
- exit 명령어 또는 Ctrl+C 입력이 들어올 경우 적절한 리턴값을 반환하여 종료

### 소스 코드

- [https://github.com/sanchoco/42_minishell](https://github.com/sanchoco/42_minishell)

### 참고 사이트

bash 레퍼런스: [https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Pipelines](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Pipelines)

쉘 스크립트 가이드: [https://mug896.github.io/bash-shell/index.html](https://mug896.github.io/bash-shell/index.html)

고급 BASH 스크립팅 가이드: [http://wiki.kldp.org/HOWTO/html/Adv-Bash-Scr-HOWTO/index.html](http://wiki.kldp.org/HOWTO/html/Adv-Bash-Scr-HOWTO/index.html)

간단한 쉘 원리: [https://bob3rdnewbie.tistory.com/124](https://bob3rdnewbie.tistory.com/124)

wait 함수: [https://ehpub.co.kr/tag/wait3/](https://ehpub.co.kr/tag/wait3/)

chdir 함수: [https://shaeod.tistory.com/325](https://shaeod.tistory.com/325)

execve 함수: [https://stackoverrun.com/ko/q/12883028](https://stackoverrun.com/ko/q/12883028)

간단한 쉘 구현: [https://hahahia.tistory.com/138](https://hahahia.tistory.com/138) 

파이프라인: [http://www.xevious7.com/linux/lpg_6_2_2.html](http://www.xevious7.com/linux/lpg_6_2_2.html)

signal 함수: [https://yechoi.tistory.com/23](https://yechoi.tistory.com/23)
