# PositionBasedonCommunicationSatellite


<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/">
    <img src="https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/Pic/logo.jpg" alt="Logo" width="200" height="120">
  </a>

  <h3 align="center">IPoS -- Position Based on Communication Satellite</h3>

</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)



<!-- ABOUT THE PROJECT -->
## About The Project
Cpomplie: Qt Creator 4.11.0  + Visual Statio 2015  and   Visual Statio 2013 BaiduMap API 
environment: win10  VS2013  and  QT 5.9.9 + Qt 5.9.9 (MSVC 2015 64-bit) + BaiduMap JavaScript API

This software has developed a positioning software based on the Iridium satellite signal based on the C/C++ language and windows + QT platform, which basically realizes the following functions:  
1. Cooperate with Novatel hardware to realize GPS-based positioning through USB serial communication and copperate with Tektronix and acchieve TekAPI-based capture function（multiple option） directly；  
2. Doppler information processing and extraction and image presentation after the hardware collects the input data (Multiple-Mode);  
3. TLE update tool mainly for Iridium and Iridium Next Satellite;  
4. Automatic identification, overhead satellite prediction and positioning based on the extracted Doppler information and the satellite number of the TLE file, and displayed on the graphical interface based on Baidu Map API;  
![Homepage](https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/Pic/Homepage.png)
![GPS](https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/Pic/GPS.png)  
![ACQ](https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/Pic/ACQ.png)  
![TLE](https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/Pic/TLE.png)  
![LOC](https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/Pic/LOC.png)  


### Built With

Base on C/QT/C++/Js
* [C](http://users.cs.cf.ac.uk/Dave.Marshall/C/CE/)
* [QT](https://doc.qt.io/)
* [C++](http://www.cplusplus.com/)
* [JavaScript](https://enable-javascript.com/)




<!-- USAGE EXAMPLES -->
## Usage

You can edit/use/run this project in QT Creator directly.  
If you want to use the IPoS directly on windows, please clone the [IPoS.zip in PositionSystem](https://github.com/BIOSmode/PositionBasedonCommunicationSatellite/blob/master/PostionSystem).




<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **extremely appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License
Distributed under the Mozilla Public License 2.0. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Your Name - sunguiyu96@gmail.com

Project Link: [https://github.com/BIOSmode/TLEDownloader](https://github.com/BIOSmode/TLEDownloader)





