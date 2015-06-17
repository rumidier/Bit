파일 구성
--------
Readme.txt : 이 파일
diskemul.c : 하드디스크 에뮬레이터
	Disk_Stat() : 하드디스크의 섹터 수를 돌려줌
	Disk_ReadSector(sector, buf)   섹터에서 512바이트를 읽어옴
	Disk_WriteSector(sector, buf)  섹터로 512바이트를 기록
	
disk_driver.h 
	디스크 에뮬레이터에서 사용하는 오류와 디스크 크기를 정의
	fs.c에서 디스크 에뮬레이터를 사용하기 위해서는 이 헤더파일을
	include해야 한다.
	
fs.c : 학생들이 작성해야 하는 파일 시스템
	비어있는 루틴들을 작성해야 한다.

fs.h : 파일 시스템의 오류 코드들이 정의되어 있음
	mini_sh.c에서 파일 시스템을 호출하기 위해서는 이 헤더파일을
	include해야 한다.

mini_sh.c : 미니 쉘로 사용자의 명령을 해석하여 파일 시스템을 호출하여
	그 결과를 화면에 보여줌.
	명령어 해석기
	

실행 파일 만들기
---------------
Linux나 UNIX에서 make명령을 수행시키면
minish 라는 실행파일이 만들어짐.
이를 실행시키면 미니 쉘이 작동한다. 미니 쉘 동작은 아래 참조.


미니 쉘 사용법
--------------
미니 쉘을 수행시키면 프롬프트가 나오고 여러분이 명령을
입력하여 수행시킬 수 있다.

[1] 프롬프트
msh # 

[2] 미니쉘 명령어들

o quit : 미니 쉘의 수행을 종료한다.
	사용 예) msh # quit

o format : 파일 시스템을 포맷한다.
      사용 예) msh # format
      
o mount : 파일 시스템을 마운트한다.
      사용 예) msh # mount

o dir : 현재 디렉토리에 존재하는 파일들을 보여준다.
	처음에 기본으로 루트 디렉토리가 현재 디렉토리가 된다.
	사용 예) msh # dir

o del : 현재 디렉토리에서 파일을 삭제한다.
	사용 예) msh # del filename

o mkfile : 현재 디렉토리에 원하는 크기의 파일을 생성한다. 파일 내용은 임의의 문자로 채운다.
	사용 예) msh # mkfile testfile 500
		이 예는 500 바이트 크기를 가지는 testfile 이름의 파일을 생성한다.
		
o type : 파일의 내용을 보여준다.
	사용 예) msh # type testfile

o mkdir : 새로운 디렉토리를 만든다.
	사용 예) msh # mkdir child_dir

o rmdir : 디렉토리를 삭제한다.
	사용 예) msh # rmdir child_dir

o cd : 새로운 디렉토리로 이동한다.
	사용 예) msh # cd child_dir
	
o fat : FAT를 보여줍니다.(학생들이 작성할 것)

o fsck : 파일 시스템 오류가 있는지를 검사 (학생들이 작성할 것)

[3] 초기 파일 시스템 테스트


학생들이 받은 파일에서 위 명령중 처음에는
quit, format, mount, dir 명령만 작동한다.
기타 명령들은 학생들이 fs.c를 완성해 나가면서 사용이 가능해진다.
이러한 명령들은 학생들이 파일 시스템을 개발하면서 테스트용으로
사용되어진다.
처음에 미니 쉘을 동작시키고 다음과 같이 포맷과 마운트를 해야만한다.

msh # format
msh # mount

msh # dir

반드시 미니 쉘을 동작시켜면 맨 먼저 format, mount 명령을 수행한 후
다른 명령을 입력한다.


