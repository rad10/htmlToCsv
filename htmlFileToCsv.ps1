$Debug = true
Function debug($content){
    if ($Debug){
        Write-Output $content
    }
}