commands 2
    set $filename = tmp->info->filename
    set $dataBegin = buffer
    set $dataEnd = buffer + bytesNeeded
    eval "dump binary memory %s 0x%lx 0x%lx", $filename, $dataBegin, $dataEnd
end