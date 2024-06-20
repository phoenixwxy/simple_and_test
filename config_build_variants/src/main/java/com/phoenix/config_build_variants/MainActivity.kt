package com.phoenix.config_build_variants

import BuildInfo
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.phoenix.config_build_variants.ui.theme.Simple_testTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()

        val buildInfo = BuildInfo()
        val name = buildInfo.getBuildType()

        setContent {
            Simple_testTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = name,
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }

        test_load_libraries()
    }

    companion object {
        init {
            System.loadLibrary("config_build_variants")
        }
    }

    external fun test_load_libraries()
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    Simple_testTheme {
        Greeting("Android")
    }
}