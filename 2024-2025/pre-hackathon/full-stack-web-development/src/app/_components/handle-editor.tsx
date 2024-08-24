"use client";

import { useState } from "react";
import { Button } from "~/components/ui/button";
import { Input } from "~/components/ui/input";
import { api } from "~/trpc/react";

export function HandleEditor({ currentHandle }: { currentHandle?: string }) {
  const [newHandle, setNewHandle] = useState(currentHandle ?? "");
  const [hasUpdatedHandle, setHasUpdatedHandle] = useState(false);
  const updateHandle = api.user.updateHandle.useMutation();

  return (
    <div className="mb-2">
      <h1>
        {(currentHandle && currentHandle.length > 0) || newHandle.length > 0
          ? `Your handle is`
          : "You don't have a handle. Create one if you'd like to be known or remain anonymous!"}
      </h1>
      <form
        onSubmit={(e) => {
          e.preventDefault();
          updateHandle.mutate(newHandle);
          setHasUpdatedHandle(true);
        }}
      >
        <Input
          placeholder="Enter your new handle"
          className="mb-2"
          value={newHandle}
          onChange={(e) => {
            setNewHandle(e.target.value);
            setHasUpdatedHandle(false);
          }}
        />
        <Button
          disabled={
            newHandle.length <= 0 ||
            currentHandle === newHandle ||
            hasUpdatedHandle
          }
          type="submit"
        >
          Update Handle
        </Button>
      </form>
    </div>
  );
}
