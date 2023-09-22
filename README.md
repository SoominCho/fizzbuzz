# fizzbuzz


# File의 고유값(Checksum) 확인하기 (Windows)
명령어
```
certutil -hashfile 파일명 SHA256|MD5
```

예제
```
certutil -hashfile java-11-openjdk-11.0.15.9-1.windows.ojdkbuild.x86_64.msi SHA256
```

# OpenJDK 다운로드 위치(11버전)
- 홈페이지: https://github.com/ojdkbuild/ojdkbuild
- 실제 다운 위치: https://github.com/ojdkbuild/ojdkbuild/releases/download/java-11-openjdk-11.0.15.9-1/java-11-openjdk-11.0.15.9-1.windows.ojdkbuild.x86_64.msi


# VS2022 MSBuild.exe 위치
```
C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe
```

## CMD에서 빌드하기
```
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" DirectXTK_Desktop_2022_Win10.vcxproj
```
따옴표를 해준 이유는, 폴더에 공백이 있기 때문



# CppCheck
## 커맨드라인 실행
```
cppcheck  --enable=all --inconclusive --xml --xml-version=2 src 2> cppcheck.xml
```

## MISRA 분석을 위한 실행
### Misra_2012.txt 파일 복사
- 위치: C:\DevTools\misra

### 설정 파일 생성: misra.json
- 위치: C:\DevTools\misra
- 파일 구성
```
{
    "script": "misra.py",
    "args": [
        "--rule-texts=C:\\DevTools\\misra\\Misra_2012.txt"
    ]
}
```

### 실행명령
```
cppcheck.exe --addon="C:\DevTools\misra\misra.json"  --xml --xml-version=2 . 2> cppcheck.xml
```

# Lizard
## 설치
CMD를 관리자 권한으로 실행 필요
```
pip install lizard
```

## 실행 명령(Command-Line for CSV)
```
lizard ./src --csv > lizard.csv
```
## CSV 출력 결과 예제
![image](https://github.com/DongJoonHan/fizzbuzz/assets/8405564/81a543e5-039e-4087-b658-3f633024eaec)



## 실행 명령(Jenkins)
```
lizard ./src --xml > lizard.xml
```
or
```
"C:\Users\cypark\AppData\Local\Programs\Python\Python310\Scripts\lizard" ./src --xml > lizard.xml
```

# CPD
## 실행 명령
실행 시, 소스코드 폴더(분석 대상 폴더)의 대소문자가 동일해야 함!!

```
cpd --minimum-tokens 100 --files ./src --language cpp --format xml > cpd.xml || exit 0
```
or
```
C:\DevTools\pmd\bin\cpd --minimum-tokens 100 --files ./src --language cpp --format xml > cpd.xml || exit 0
```

뒤에 ||exit 0 이 있는 이유는, Jenkins는 exit 0을 정상이라고 보고, 나머지는 빌드 실패라 판단하는데 CPD는 기본으로 exit 1과 같은 방식으로 종료해서, 정상 처리해도 빌드 실패가 발생함. 이를 예방하기 위해 exit 0을 추가함.

# CLOC (라인수, 주석라인수 확인)
## 다운로드
https://github.com/AlDanial/cloc

## 사용법
```
cloc.exe .
```

# Pipeline
```
pipeline {
    agent any 
    
    environment {
        MSBUILD_PATH = 'C://Program Files//Microsoft Visual Studio//2022//Community//MSBuild//Current//Bin//MSBuild.exe'  
    }

    stages {
        stage('Checkout') {
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: '*/main']],
                    doGenerateSubmoduleConfigurations: false,
                    extensions: [],
                    submoduleCfg: [],
                    userRemoteConfigs: [[url: 'https://github.com/microsoft/DirectXTK12.git']]
                ])
            }
        }

        stage('Build') {
            steps {
                bat "\"${env.MSBUILD_PATH}\" DirectXTK_Desktop_2022_Win10.vcxproj"  
            }
        }
        
        stage('Verification') {
            steps {
                bat "\"C://Program Files//Cppcheck//cppcheck.exe\"  --enable=all --inconclusive --xml --xml-version=2 src 2> cppcheck.xml"
                recordIssues enabledForFailure: true, aggregatingResults: true, tool: cppCheck(pattern: 'cppcheck.xml')
            }
        }
    }
}
```
# Jenkins Node
## Windows 시작 시 연결을 위한 bat 파일 생성
가정: runNode.bat 이라 가정
```
cd c:\Jenkins
java -jar agent.jar -jnlpUrl http://172.16.2.26/computer/Win10_VM/jenkins-agent.jnlp -secret 90b6ee882eaddf4404c12db7db2a59ab30c56a283126d6da93d1edc7caf9a3cd -workDir "C:\Jenkins"
```

## 시작프로그램 등록
1. 시작+R 키로 "실행"을 실행
2. shell:startup 입력해서 실행
3. 시작 프로그램에 runNode.bat 복사
