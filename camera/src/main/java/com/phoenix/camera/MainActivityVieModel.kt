package com.phoenix.camera

import androidx.lifecycle.ViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow

class MainActivityVieModel : ViewModel() {
    private val _mainTextState = MutableStateFlow(MainTextState())
    val uiState = _mainTextState.asStateFlow()

    fun updateUiState(newMainTextState: MainTextState) {
        newMainTextState.also { _mainTextState.value = it }
    }
}

data class MainTextState(
    val globalInfo: String = ""
)
