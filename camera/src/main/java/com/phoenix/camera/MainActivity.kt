package com.phoenix.camera

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.content.res.Configuration
import android.os.Bundle
import android.util.Log
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.ViewGroup
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.viewinterop.AndroidView
import androidx.core.content.ContextCompat
import com.phoenix.camera.ui.theme.Simple_testTheme
import kotlin.math.sqrt

class MainActivity : ComponentActivity() {
    companion object {
        val TAG: String = MainActivity::class.java.simpleName
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        Log.i(TAG, "onCreate: PhoenixDebug")
        requestCameraPermission()
        setContent {
            Simple_testTheme {
                TODO("update")
                DefaultDisplayView()
            }
        }

        Log.e(TAG, "onCreate: " + sqrt(5.0))
        Log.i(TAG, "onCreate: " + sqrt(5.0))
    }

    private val requestPermissionLauncher = registerForActivityResult(
        ActivityResultContracts.RequestMultiplePermissions()
    ) { permissions ->
        val granted = permissions.entries.all {
            it.value
        }
        if (granted) {
            // 权限被授予，可以继续使用相机
            startCamera()
        } else {
            // 权限被拒绝，提示用户
            Toast.makeText(this, "Camera permission is required", Toast.LENGTH_SHORT).show()
        }
    }

    private fun requestCameraPermission() {
        val permissions = arrayOf(
            Manifest.permission.CAMERA
        )
        if (!hasPermissions(this, *permissions)) {
            requestPermissionLauncher.launch(permissions)
        } else {
            startCamera()
        }
    }

    private fun hasPermissions(context: Context, vararg permissions: String): Boolean {
        for (permission in permissions) {
            if (ContextCompat.checkSelfPermission(
                    context,
                    permission
                ) != PackageManager.PERMISSION_GRANTED
            ) {
                return false
            }
        }
        return true
    }

    private fun startCamera() {
        // 启动相机的代码
    }
}

@Composable
fun ComposableSurfaceView(modifier: Modifier = Modifier) {
    AndroidView(factory = { context ->
        SurfaceView(context).apply {
            layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
            )
            holder.addCallback(object : SurfaceHolder.Callback {
                override fun surfaceCreated(p0: SurfaceHolder) {
                    // 在这里进行绘制操作
                }

                override fun surfaceChanged(p0: SurfaceHolder, p1: Int, p2: Int, p3: Int) {}

                override fun surfaceDestroyed(p0: SurfaceHolder) {}
            })
        }
    }, modifier = modifier)
}

@Composable
fun MultipleSurfaceViews() {
    val num = 12
    val colTmp = sqrt(num.toDouble())
    val tmp: Int = colTmp.toInt()
    val col = num / tmp
    LazyVerticalGrid(columns = GridCells.Fixed(col)) {
        items(count = num) { index ->
            ComposableSurfaceView(modifier = Modifier.fillMaxWidth())
        }
    }
}

@Composable
fun BoxWithBorder(
    modifier: Modifier = Modifier,
    borderSize: Int = 1,
    borderColor: Color = Color.Black,
    content: @Composable () -> Unit
) {
    Box(
        modifier = modifier
            .background(color = Color.LightGray)
            .border(
                border = BorderStroke(width = borderSize.dp, color = borderColor),
                shape = RoundedCornerShape(4.dp)
            )
    ) {
        content()
    }
}

@Composable
fun SideBySideLayout(
    modifier: Modifier = Modifier,
    sideContent: @Composable () -> Unit,
    mainContent: @Composable () -> Unit
) {
    Row(
        modifier = modifier.fillMaxSize(),
        verticalAlignment = Alignment.CenterVertically
    ) {
        // 侧边栏内容，带有边框
        BoxWithBorder(
            modifier = Modifier
                .width(100.dp) // 侧边栏宽度
                .fillMaxHeight() // 填满高度
        ) {
            sideContent()
        }
        // 主内容区域，可以是 AndroidView
        Box(
            modifier = Modifier
                .weight(1f) // 占据剩余空间
                .fillMaxHeight() // 填满高度
        ) {
            mainContent()
        }
    }
}

@Composable
fun DefaultDisplayView() {
    SideBySideLayout(
        sideContent = {
            // 侧边栏内容，例如文本
            Text(
                text = "Side Panel",
                fontSize = 18.sp
            )
        },
        mainContent = {
            // 主内容区域
            MultipleSurfaceViews()
        }
    )
}

@Preview(showBackground = true, device = "spec:parent=pixel_5,orientation=landscape")
@Composable
fun GreetingPreview() {
    Simple_testTheme {
//        Greeting("Android")
        DefaultDisplayView()
    }
}