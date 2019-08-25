<p align="center"> <img src=/Preview.png></p>
AEColorPicker
================
This is the Plugin and ExternalLibrary for Adobe After Effects, is intended to access from scripts to the built-in AE ColorPickerDialog, instead of the operating system dialog.

<!--
Project page:
* https://github.com/Belonit/AEColorPicker
Download:       
* https://github.com/Belonit/AEColorPicker
-->

Installing the plug-in for Adobe After Effects
-------
**Windows:**

Copy AEColorPicker.aex to the folder
> Program Files\Adobe\Adobe After Effects [version]\Support Files\Plug-ins

**Mac:**
Copy AEColorPicker.plugin to the folder
> Applications/Adobe After Effects [version]/Plug-ins


An example of using ExternalLibrary in JSX scripts.
-------
```js
var externalLibrary = new ExternalObject('lib:C:\\AEColorPicker.aex'); 
var oldColor = 0x20F186;
var newColor = externalLibrary.colorPicker(oldColor, "dialog_title");
if(newColor == -1){ //Returns -1 if user clicked on cancel
    newColor = oldColor;
}
```

Building
-------
Visual Studio 2019 for Window, XCode 8 for MAC. Other than that, you will need [Adobe After Effects SDK](https://www.adobe.io/apis/creativecloud/aftereffects.html) and [Adobe Bridge SDK](https://www.adobe.io/apis/creativecloud/bridge.html). Installation instructions for SDKs are located in the corresponding subfolders in the [/SDK/](/SDK/)


Future plans
-------
Make ExternalLibraries work with other Adobe programs