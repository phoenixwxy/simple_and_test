package com.phoenix.camera

import android.hardware.camera2.CameraManager

object CamManager {
    val TAG : String = CamManager::class.java.simpleName

    fun CamManager() {
    }

    fun getCameraList() : (CameraManager) -> Array<String> {
        val camList : (CameraManager) -> Array<String> = CameraManager::getCameraIdList
        val lsit = camList.toString()
        return camList
    }
}