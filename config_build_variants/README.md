# Config and build Variants

Every module's root path is its name's path in build.gradle.kts

## variants

## sourceSets
the binary libraries set the path to the module
if in `main`, Android Studio can include `jniLibs` by default.
if we want to include the libraries in another paths, we should add the code:
```groovy
android {
    sourceSets {
        getByName("main") {
            jniLibs.srcDirs("jniLibs", "src/main/libs")
        }
    }
}
```