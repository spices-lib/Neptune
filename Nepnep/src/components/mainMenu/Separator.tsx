export default function Separator({
    color,
    height
}: {
    color: string
    height?: number
}) {
    return (
        <div className={`flex flex-col h-[${height ?? 10}px] w-full bg-[${color}]`}></div>
    )
}