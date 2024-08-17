plugins {
    alias(libs.plugins.androidLibrary)
    alias(libs.plugins.jetbrainsKotlinAndroid)
}

android {
    namespace = "com.example.cpp_module"
    compileSdk = 34

    defaultConfig {
        minSdk = 29

        externalNativeBuild {
            cmake {
                cppFlags += "-DANDROID_STL=c++_shared, -std=c++17"
                targets += setOf("cpp_module", "stl_learn", "os_learn")
            }
        }

        ndk {
            abiFilters += "arm64-v8a"
        }
    }

    buildTypes {
        debug {
        }
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }

    externalNativeBuild {
        cmake {
            path = file(project.projectDir.toString() + "/CMakeLists.txt")
            version = "3.22.1"
        }
    }
    ndkVersion = "26.2.11394342"
}

dependencies {
}