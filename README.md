# pico-blink-easy
Pico example which automatically download the SDK. 

# 説明
このプログラムはRaspberryPi Picoのサンプルです。

ビルド中にpico-sdkをダウンロードするため、あらかじめpico-sdkを
設定する必要がありません。

Ubuntu 22.04でテスト済みです。

# ビルド環境の構築
[rpi_pico_env_setup](https://github.com/suikan4github/rpi_pico_env_setup) のスクリプトを使って環境設定を行ってください。

このスクリプトはビルドに必要なツール類をインストールします。

# Linuxコマンドラインでのビルド
コマンドラインから実行する場合は、以下のコマンドを実行してください。
```bash
# Configure project
mkdir build
cd build
cmake ..

# Build project
cd ..
cmake --build build 
```
この間、Pico-sdkのダウンロードも行うため、少し時間がかかります。

ビルド結果はbuildサブディレクトリに出力されます。

# VS Codeでのビルド(Linux, WSL)

VS Codeを起動したら、メニューバーの File -> Open Folder... でプロジェクトディレクトリを開きます。


## VS Codeの設定
VS Codeの拡張機能に[C/C++ Extention Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)をインストールしてください。

この拡張機能はC++言語のシンタックス・ハイライティングやIntelli-senseによる入力保管を行う他、CMake拡張機能も含んでいます。
## ビルド
コマンドパレット(ctrl-shift-P)から、
```
Cmake : Configure
```
を実行してください。CMake拡張機能が自動的にコンパイラを探し出してプロジェクトのコンフィギュレーションを行います。この間、Pico-sdkのダウンロードも行うため、少し時間がかかります。

念の為、ステータスバーでコンパイラがGCC XX.X.X arm-none-eabiで有ることを確認してください。下の図の例ではGCC 10.3.1 arm-none-eabiになっています。

![](image/Screenshot_startus_bar.png)

arm-none-eabiではない場合には、ステータスバーの当該位置をクリックすることで、メニューバーからプルダウンが現れますので適切なコンパイラを選んでください。

![](image/Screenshot_compiler_pull_down.png)

コンパイラを選び終わったら、ステータスバーのBuildをクリックすることでビルドすることができます。

ビルド結果はbuildサブディレクトリに出力されます。

# Windowsコマンドプロンプトでのビルド 

Windowsでビルドする場合、通常のコマンドプロンプトではビルドできません。WindowsのStartメニューから専用のPico - Developper Command Promptを使ってください。

コマンドプロンプトが現れたらプロジェクトディレクトリに移ります。あとは、Linuxのときと同じです。

```cmd
REM Configure project
mkdir build
cd build
cmake .. 

REM Build project
cd ..
cmake --build build 
```
Windowsの場合も、Pico-sdkのダウンロードも行うため、少し時間がかかります。

ビルド結果はbuildサブディレクトリに出力されます。


# VS Codeでのビルド(Windows)

普段使いのVS Codeを起動してもビルドできません。WindowsのStartメニューから専用の Pico - Visual Studio Code を起動してください。

次に、メニューバーの File -> Open Folder... でプロジェクトディレクトリを開きます。

## VS Codeの設定
VS Codeの拡張機能に[C/C++ Extention Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)をインストールしてください。

この拡張機能はC++言語のシンタックス・ハイライティングやIntelli-senseによる入力保管を行う他、CMake拡張機能も含んでいます。

なお、インストールはローカルではなくWSLに対して行います。
## ビルド
コマンドパレット(ctrl-shift-P)から、
```
Cmake : Configure
```
を実行してください。CMake拡張機能が自動的にコンパイラを探し出してプロジェクトのコンフィギュレーションを行います。この間、Pico-sdkのダウンロードも行うため、少し時間がかかります。

念の為、ステータスバーでコンパイラがGCC XX.X.X arm-none-eabiで有ることを確認してください。下の図の例ではGCC 10.3.1 arm-none-eabiになっています。

![](image/Screenshot_startus_bar.png)

arm-none-eabiではない場合には、ステータスバーの当該位置をクリックすることで、メニューバーからプルダウンが現れますので適切なコンパイラを選んでください。

![](image/Screenshot_compiler_pull_down.png)

コンパイラを選び終わったら、ステータスバーのBuildをクリックすることでビルドすることができます。

ビルド結果はbuildサブディレクトリに出力されます。
