package com.phoenix.biometric

import android.content.DialogInterface
import android.hardware.biometrics.BiometricManager
import android.hardware.biometrics.BiometricManager.Authenticators.BIOMETRIC_STRONG
import android.hardware.biometrics.BiometricManager.Authenticators.BIOMETRIC_WEAK
import android.hardware.biometrics.BiometricManager.Authenticators.DEVICE_CREDENTIAL
import android.hardware.biometrics.BiometricManager.BIOMETRIC_SUCCESS
import android.hardware.biometrics.BiometricPrompt
import android.os.Bundle
import android.os.CancellationSignal
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.phoenix.biometric.ui.theme.Simple_testTheme

class MainActivity : ComponentActivity() {

    private val mContext = this
    private lateinit var mBiometricManager : BiometricManager
    private lateinit var mBiometricPrompt: BiometricPrompt
    private val mCancellationSignal: CancellationSignal = CancellationSignal()

    private val mAuthenticationCallback: BiometricPrompt.AuthenticationCallback =
        object : BiometricPrompt.AuthenticationCallback() {
            override fun onAuthenticationError(errorCode: Int, errString: CharSequence?) {
                super.onAuthenticationError(errorCode, errString)
                Log.i(TAG, "onAuthenticationError $errString");
            }

            override fun onAuthenticationHelp(helpCode: Int, helpString: CharSequence?) {
                super.onAuthenticationHelp(helpCode, helpString)

            }

            override fun onAuthenticationSucceeded(result: BiometricPrompt.AuthenticationResult?) {
                super.onAuthenticationSucceeded(result)
                Log.i(TAG, "onAuthenticationSucceeded " + result.toString());
                Toast.makeText(mContext,  "指纹验证成功", Toast.LENGTH_LONG).show()
            }

            override fun onAuthenticationFailed() {
                super.onAuthenticationFailed()
                Log.i(TAG, "onAuthenticationFailed ");
            }
        }

    companion object {
        val TAG: String = MainActivity::class.java.simpleName
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            Simple_testTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding),
                        onFingerprintClick = { onFingerprintClick() },
                        onFaceClick = { onFaceClick() }
                    )
                }
            }
        }

        mBiometricManager = getSystemService(BIOMETRIC_SERVICE) as BiometricManager

        if (BIOMETRIC_SUCCESS == mBiometricManager.canAuthenticate(BIOMETRIC_STRONG)) {
            Toast.makeText(mContext,  "Strong", Toast.LENGTH_SHORT).show()
        } else if (BIOMETRIC_SUCCESS == mBiometricManager.canAuthenticate(BIOMETRIC_WEAK)) {
            Toast.makeText(mContext,  "Weak", Toast.LENGTH_SHORT).show()
        } else if (BIOMETRIC_SUCCESS == mBiometricManager.canAuthenticate(DEVICE_CREDENTIAL)) {
            Toast.makeText(mContext,  "Weak", Toast.LENGTH_SHORT).show()
        } else {
            Toast.makeText(mContext,  "None", Toast.LENGTH_SHORT).show()
        }

        mCancellationSignal.setOnCancelListener(object : CancellationSignal.OnCancelListener {
            override fun onCancel() {
                Log.i(TAG, "onCancel: Canceled")
            }
        })


//        val faceManager = getSystemService(FaceManager.class) as FaceManager
    }

    fun onFingerprintClick() {
        mBiometricPrompt = BiometricPrompt.Builder(this)
            .setTitle("指纹验证")
            .setDescription("描述")
            .setNegativeButton("取消", mainExecutor, object : DialogInterface.OnClickListener {
                override fun onClick(dialog: DialogInterface?, which: Int) {
                    Log.i(TAG, "onClick: Cancel button clicked")
                }

            })
            .build();

        mBiometricPrompt.authenticate(mCancellationSignal, mainExecutor, mAuthenticationCallback)
    }

    fun onFaceClick() {
        mBiometricPrompt = BiometricPrompt.Builder(this)
            .setTitle("人脸验证")
            .setDescription("描述")
            .setAllowedAuthenticators(BIOMETRIC_STRONG)
            .setNegativeButton("取消", mainExecutor
            ) { dialog, which -> Log.i(TAG, "onClick: Cancel button clicked") }
            .build();

        mBiometricPrompt.authenticate(mCancellationSignal, mainExecutor, mAuthenticationCallback)
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier, onFingerprintClick: () -> Unit, onFaceClick: () -> Unit) {
    Column {
        Text(
            text = "Hello $name!",
            modifier = modifier
        )

        Button(onClick = onFingerprintClick) {
            Text(text = "Fingerprint")
        }

        Button(onClick = onFingerprintClick) {
            Text(text = "Face")
        }
    }
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    Simple_testTheme {
        Simple_testTheme {
            Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                Greeting(
                    name = "Android",
                    modifier = Modifier.padding(innerPadding),
                    onFingerprintClick = { MainActivity::onFingerprintClick },
                    onFaceClick = { MainActivity::onFaceClick }
                )
            }
        }
    }
}